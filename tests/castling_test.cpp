#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/moves/move_type.h"
#include "chess/pieces/bishop.h"
#include "chess/pieces/king.h"
#include "chess/pieces/knight.h"
#include "chess/pieces/pawn.h"
#include "chess/pieces/piece_type.h"
#include "chess/pieces/rook.h"
#include "chess/player.h"
#include "chess/position.h"
#include <algorithm>
#include <array>
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <memory>

namespace {

constexpr auto colours = std::array{chess::Colour::White, chess::Colour::Black};

chess::Position home(chess::Colour colour, int file) {
    return {colour == chess::Colour::White ? 0 : 7, file};
}

void prepare_castling(chess::Board &board, chess::Colour colour) {
    for (int rank = 0; rank < board.dimension(); ++rank) {
        for (int file = 0; file < board.dimension(); ++file) {
            board[chess::Position{rank, file}] = nullptr;
        }
    }
    board[home(colour, 4)] = std::make_unique<chess::King>(colour);
    board[home(colour, 0)] = std::make_unique<chess::Rook>(colour);
    board[home(colour, 7)] = std::make_unique<chess::Rook>(colour);
    const auto enemy = chess::opponent(colour);
    board[home(enemy, 4)] = std::make_unique<chess::King>(enemy);
}

bool offers_castle(chess::Board &board, chess::Colour colour, chess::MoveType type) {
    const chess::GameState game{colour, board};
    const auto moves = game.available_moves_for_piece(home(colour, 4));
    return std::ranges::any_of(moves, [type](const auto &move) { return move->type() == type; });
}

}

TEST_CASE("Both castling sides are offered with clear paths and unmoved pieces") {
    for (const auto colour : colours) {
        CAPTURE(colour);
        chess::Board board;
        prepare_castling(board, colour);
        const chess::GameState game{colour, board};
        const auto moves = game.available_moves_for_piece(home(colour, 4));

        for (const auto type :
             std::array{chess::MoveType::CastleKingSide, chess::MoveType::CastleQueenSide}) {
            const auto castle = std::ranges::find_if(moves, [type](const auto &move) {
                return move->type() == type;
            });
            REQUIRE(castle != moves.end());
            REQUIRE((*castle)->from() == home(colour, 4));
            REQUIRE(
                (*castle)->to() == home(colour, type == chess::MoveType::CastleKingSide ? 6 : 2)
            );
        }
    }
}

TEST_CASE("A king that has moved cannot castle on either side") {
    for (const auto colour : colours) {
        chess::Board board;
        prepare_castling(board, colour);
        board[home(colour, 4)]->set_has_moved();
        REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleKingSide));
        REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleQueenSide));
    }
}

TEST_CASE("A moved rook prevents only its own side's castling") {
    for (const auto colour : colours) {
        for (const auto rook_file : std::array{0, 7}) {
            CAPTURE(colour, rook_file);
            chess::Board board;
            prepare_castling(board, colour);
            board[home(colour, rook_file)]->set_has_moved();
            REQUIRE(
                offers_castle(board, colour, chess::MoveType::CastleKingSide) == (rook_file == 0)
            );
            REQUIRE(
                offers_castle(board, colour, chess::MoveType::CastleQueenSide) == (rook_file == 7)
            );
        }
    }
}

TEST_CASE("Castling requires a same-colour rook on its starting square") {
    for (const auto colour : colours) {
        for (const auto scenario : std::array{0, 1, 2}) {
            CAPTURE(colour, scenario);
            chess::Board board;
            prepare_castling(board, colour);

            if (scenario == 0) {
                board[home(colour, 0)] = nullptr;
                board[home(colour, 7)] = nullptr;
            } else if (scenario == 1) {
                board[home(colour, 0)] = std::make_unique<chess::Bishop>(colour);
                board[home(colour, 7)] = std::make_unique<chess::Knight>(colour);
            } else {
                board[home(colour, 0)] = std::make_unique<chess::Rook>(chess::opponent(colour));
                board[home(colour, 7)] = std::make_unique<chess::Rook>(chess::opponent(colour));
            }
            REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleKingSide));
            REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleQueenSide));
        }
    }
}

TEST_CASE("Every square between king and rook must be empty including the queenside b-file") {
    for (const auto colour : colours) {
        for (const auto file : std::array{1, 2, 3, 5, 6}) {
            CAPTURE(colour, file);
            chess::Board board;
            prepare_castling(board, colour);
            board[home(colour, file)] = std::make_unique<chess::Knight>(colour);
            REQUIRE(offers_castle(board, colour, chess::MoveType::CastleKingSide) == (file < 4));
            REQUIRE(offers_castle(board, colour, chess::MoveType::CastleQueenSide) == (file > 4));
        }
    }
}

TEST_CASE("A king cannot castle out of check") {
    for (const auto colour : colours) {
        chess::Board board;
        prepare_castling(board, colour);
        const auto attacker = chess::Position{colour == chess::Colour::White ? 3 : 4, 4};
        board[attacker] = std::make_unique<chess::Rook>(chess::opponent(colour));
        REQUIRE(board.is_in_check(colour));
        REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleKingSide));
        REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleQueenSide));
    }
}

TEST_CASE("A king cannot castle across or onto an attacked square") {
    for (const auto colour : colours) {
        for (const auto file : std::array{2, 3, 5, 6}) {
            CAPTURE(colour, file);
            chess::Board board;
            prepare_castling(board, colour);
            const auto attacker = chess::Position{colour == chess::Colour::White ? 3 : 4, file};
            board[attacker] = std::make_unique<chess::Rook>(chess::opponent(colour));
            REQUIRE_FALSE(board.is_in_check(colour));
            REQUIRE(offers_castle(board, colour, chess::MoveType::CastleKingSide) == (file < 4));
            REQUIRE(offers_castle(board, colour, chess::MoveType::CastleQueenSide) == (file > 4));
        }
    }
}

TEST_CASE("Pawn attacks on empty transit squares prevent castling") {
    for (const auto colour : colours) {
        chess::Board board;
        prepare_castling(board, colour);
        // e2/e7 attacks both d1/d8 and f1/f8 without checking the king on e1/e8.
        const auto pawn_square = chess::Position{colour == chess::Colour::White ? 1 : 6, 4};
        board[pawn_square] = std::make_unique<chess::Pawn>(chess::opponent(colour));
        REQUIRE_FALSE(board.is_in_check(colour));
        REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleKingSide));
        REQUIRE_FALSE(offers_castle(board, colour, chess::MoveType::CastleQueenSide));
    }
}

TEST_CASE("Attacks on the queenside rook or b-file do not prevent castling") {
    for (const auto colour : colours) {
        for (const auto file : std::array{0, 1}) {
            chess::Board board;
            prepare_castling(board, colour);
            const auto attacker = chess::Position{colour == chess::Colour::White ? 3 : 4, file};
            board[attacker] = std::make_unique<chess::Rook>(chess::opponent(colour));
            REQUIRE(offers_castle(board, colour, chess::MoveType::CastleQueenSide));
        }
    }
}

TEST_CASE("Executing castling moves both pieces marks them moved and advances the turn") {
    for (const auto colour : colours) {
        for (const auto kingside : std::array{true, false}) {
            CAPTURE(colour, kingside);
            chess::Board board;
            prepare_castling(board, colour);
            chess::GameState game{colour, board};
            const auto king_from = home(colour, 4);
            const auto rook_from = home(colour, kingside ? 7 : 0);
            const auto king_to = home(colour, kingside ? 6 : 2);
            const auto rook_to = home(colour, kingside ? 5 : 3);
            const auto type =
                kingside ? chess::MoveType::CastleKingSide : chess::MoveType::CastleQueenSide;
            const auto *king = board[king_from].get();
            const auto *rook = board[rook_from].get();
            const auto moves = game.available_moves_for_piece(king_from);
            const auto castle = std::ranges::find_if(moves, [type](const auto &move) {
                return move->type() == type;
            });
            REQUIRE(castle != moves.end());
            // Generating and filtering a castle must not execute it on the real board.
            REQUIRE(board[king_from].get() == king);
            REQUIRE(board[rook_from].get() == rook);
            REQUIRE_FALSE(king->has_moved());
            REQUIRE_FALSE(rook->has_moved());

            game.execute_move(**castle);
            REQUIRE(board.is_empty(king_from));
            REQUIRE(board.is_empty(rook_from));
            REQUIRE(board[king_to].get() == king);
            REQUIRE(board[rook_to].get() == rook);
            REQUIRE(board[king_to]->type() == chess::PieceType::King);
            REQUIRE(board[rook_to]->type() == chess::PieceType::Rook);
            REQUIRE(board[king_to]->colour() == colour);
            REQUIRE(board[rook_to]->colour() == colour);
            REQUIRE(king->has_moved());
            REQUIRE(rook->has_moved());
            REQUIRE(game.current_player() == chess::opponent(colour));
        }
    }
}
