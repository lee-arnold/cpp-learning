#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "chess/pieces/bishop.h"
#include "chess/pieces/king.h"
#include "chess/pieces/knight.h"
#include "chess/pieces/pawn.h"
#include "chess/pieces/queen.h"
#include "chess/pieces/rook.h"
#include "chess/player.h"
#include "chess/position.h"
#include "helpers/moves.h"
#include "helpers/squares.h"
#include <algorithm>
#include <array>
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>

using namespace test_squares;

namespace {

void clear_board(chess::Board &board) {
    for (int rank = 0; rank < board.dimension(); ++rank) {
        for (int file = 0; file < board.dimension(); ++file) {
            board[chess::Position{rank, file}] = nullptr;
        }
    }
}

}

TEST_CASE("Check detection identifies attacks on either colour's king and respects blockers") {
    for (const auto colour : std::array{chess::Colour::White, chess::Colour::Black}) {
        CAPTURE(colour);

        chess::Board board;
        clear_board(board);

        const auto enemy = chess::opponent(colour);
        const auto king_square = colour == chess::Colour::White ? e1 : e8;
        const auto enemy_king_square = colour == chess::Colour::White ? a8 : a1;
        const auto attacker_square = colour == chess::Colour::White ? e7 : e2;
        const auto blocker_square = colour == chess::Colour::White ? e4 : e5;

        board[king_square] = std::make_unique<chess::King>(colour);
        board[enemy_king_square] = std::make_unique<chess::King>(enemy);

        REQUIRE_FALSE(board.is_in_check(colour));

        board[attacker_square] = std::make_unique<chess::Rook>(enemy);

        REQUIRE(board.is_in_check(colour));
        REQUIRE_FALSE(board.is_in_check(enemy));

        board[blocker_square] = std::make_unique<chess::Pawn>(colour);

        REQUIRE_FALSE(board.is_in_check(colour));

        board[blocker_square] = std::make_unique<chess::Pawn>(enemy);

        REQUIRE_FALSE(board.is_in_check(colour));
    }
}

TEST_CASE("Bishops queens and knights can give check") {
    chess::Board board;
    clear_board(board);

    board[e1] = std::make_unique<chess::King>(chess::Colour::White);
    board[a8] = std::make_unique<chess::King>(chess::Colour::Black);

    SECTION("Bishop diagonal") {
        board[h4] = std::make_unique<chess::Bishop>(chess::Colour::Black);
        REQUIRE(board.is_in_check(chess::Colour::White));
        board[f2] = std::make_unique<chess::Pawn>(chess::Colour::White);
        REQUIRE_FALSE(board.is_in_check(chess::Colour::White));
    }

    SECTION("Queen diagonal") {
        board[h4] = std::make_unique<chess::Queen>(chess::Colour::Black);
        REQUIRE(board.is_in_check(chess::Colour::White));
    }

    SECTION("Knight jumps over blockers") {
        board[f3] = std::make_unique<chess::Knight>(chess::Colour::Black);
        board[f2] = std::make_unique<chess::Pawn>(chess::Colour::White);
        REQUIRE(board.is_in_check(chess::Colour::White));
    }
}

TEST_CASE("Pawns check diagonally rather than straight ahead for either colour") {
    for (const auto colour : std::array{chess::Colour::White, chess::Colour::Black}) {
        CAPTURE(colour);

        chess::Board board;
        clear_board(board);

        const auto enemy = chess::opponent(colour);
        const auto king_square = colour == chess::Colour::White ? e4 : e5;
        const auto diagonal = colour == chess::Colour::White ? d5 : d4;
        const auto ahead = colour == chess::Colour::White ? e5 : e4;

        board[king_square] = std::make_unique<chess::King>(colour);
        board[a8] = std::make_unique<chess::King>(enemy);
        board[diagonal] = std::make_unique<chess::Pawn>(enemy);

        REQUIRE(board.is_in_check(colour));

        relocate_piece(board, diagonal, ahead);

        REQUIRE_FALSE(board.is_in_check(colour));
    }
}

TEST_CASE("Kings cannot move adjacent to the opposing king") {
    chess::Board board;
    clear_board(board);

    board[e1] = std::make_unique<chess::King>(chess::Colour::White);
    board[e3] = std::make_unique<chess::King>(chess::Colour::Black);

    chess::GameState game{chess::Colour::White, board};
    const auto destinations = get_destinations_for_piece(game, e1);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, d1) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f1) != destinations.end());

    relocate_piece(board, e3, e2);

    REQUIRE(board.is_in_check(chess::Colour::White));
    REQUIRE(board.is_in_check(chess::Colour::Black));
}

TEST_CASE(
    "A pinned rook can stay on its pin line or capture the attacker but cannot expose its king"
) {
    chess::Board board;
    clear_board(board);

    board[e1] = std::make_unique<chess::King>(chess::Colour::White);
    board[e2] = std::make_unique<chess::Rook>(chess::Colour::White);
    board[e8] = std::make_unique<chess::Rook>(chess::Colour::Black);
    board[a8] = std::make_unique<chess::King>(chess::Colour::Black);

    chess::GameState game{chess::Colour::White, board};
    const auto destinations = get_destinations_for_piece(game, e2);

    REQUIRE(destinations.size() == 6);
    REQUIRE(std::ranges::all_of(destinations, [](chess::Position position) {
        return position.file() == e2.file();
    }));
    REQUIRE(std::ranges::find(destinations, e8) != destinations.end());
    REQUIRE_FALSE(board.is_in_check(chess::Colour::White));
}

TEST_CASE("While in check only moves that remove the threat are available") {
    chess::Board board;
    clear_board(board);

    board[e1] = std::make_unique<chess::King>(chess::Colour::White);
    board[a2] = std::make_unique<chess::Rook>(chess::Colour::White);
    board[e8] = std::make_unique<chess::Rook>(chess::Colour::Black);
    board[a8] = std::make_unique<chess::King>(chess::Colour::Black);

    chess::GameState game{chess::Colour::White, board};

    REQUIRE(board.is_in_check(chess::Colour::White));

    const auto rook_destinations = get_destinations_for_piece(game, a2);

    REQUIRE(rook_destinations.size() == 1);
    REQUIRE(rook_destinations.front() == e2);

    const auto king_destinations = get_destinations_for_piece(game, e1);

    REQUIRE(std::ranges::find(king_destinations, f1) != king_destinations.end());
    REQUIRE(std::ranges::find(king_destinations, e2) == king_destinations.end());
}
