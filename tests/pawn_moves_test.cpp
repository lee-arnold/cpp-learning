#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/moves/pawn_promotion.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <memory>
#include <set>
#include <vector>

using namespace test_squares;

namespace {

std::set<chess::PieceType> get_piece_types_for_promotion(
    const std::vector<std::unique_ptr<chess::Move>> &moves, chess::Position position
) {
    std::set<chess::PieceType> piece_types{};

    for (const auto &move : moves) {
        if (move->to() != position) continue;
        const auto *promotion = dynamic_cast<const chess::PawnPromotionMove *>(move.get());
        if (!promotion) continue;

        piece_types.insert(promotion->piece_type());
    }

    return piece_types;
}

}

TEST_CASE("An unmoved white pawn with a clear path can advance one or two squares") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("An unmoved black pawn with a clear path can advance one or two squares, or capture") {
    chess::Board board;
    chess::GameState game{chess::Colour::Black, board};

    relocate_piece(board, a2, g6, true);
    const auto destinations = get_destinations_for_piece(game, h7);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, h6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, h5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, g6) != destinations.end());
}

TEST_CASE("A previously moved pawn with a clear path can advance only one square") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a2, a3, true);

    const auto destinations = get_destinations_for_piece(game, a3);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("A friendly piece immediately ahead prevents all pawn forward moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b2, a3);

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(moves.empty());
}

TEST_CASE("An enemy piece immediately ahead prevents all pawn forward moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b7, a3);

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(moves.empty());
}

TEST_CASE("A friendly piece two squares ahead allows only the one-square pawn advance") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b2, a4);
    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
}

TEST_CASE("An enemy piece two squares ahead allows only the one-square pawn advance") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b7, a4);
    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
}

TEST_CASE("An unmoved white pawn one rank from the edge offers four promotion choices") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    clear_piece(board, a8);
    clear_piece(board, b8);
    relocate_piece(board, a2, a7);

    auto moves = game.available_moves_for_piece(a7);

    REQUIRE(moves.size() == 4);

    auto piece_types = get_piece_types_for_promotion(moves, a8);

    REQUIRE(piece_types.contains(chess::PieceType::Queen));
    REQUIRE(piece_types.contains(chess::PieceType::Rook));
    REQUIRE(piece_types.contains(chess::PieceType::Bishop));
    REQUIRE(piece_types.contains(chess::PieceType::Knight));
}

TEST_CASE("An unmoved black pawn one rank from the edge offers four promotion choices") {
    chess::Board board;
    chess::GameState game{chess::Colour::Black, board};

    clear_piece(board, a1);
    clear_piece(board, b1);
    relocate_piece(board, a7, a2);

    auto moves = game.available_moves_for_piece(a2);

    REQUIRE(moves.size() == 4);

    auto piece_types = get_piece_types_for_promotion(moves, a1);

    REQUIRE(piece_types.contains(chess::PieceType::Queen));
    REQUIRE(piece_types.contains(chess::PieceType::Rook));
    REQUIRE(piece_types.contains(chess::PieceType::Bishop));
    REQUIRE(piece_types.contains(chess::PieceType::Knight));
}

TEST_CASE("Moves generated for a pawn start at the pawn's current square") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto source_positions = get_source_positions_for_piece(game, a2);

    REQUIRE(!source_positions.empty());
    REQUIRE(std::ranges::all_of(source_positions, [](const auto &position) {
        return position == a2;
    }));
}

TEST_CASE("Querying pawn moves leaves the pawn and its forward squares unchanged.") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto a2_ptr = board[a2].get();
    auto a3_ptr = board[a3].get();
    auto a4_ptr = board[a4].get();

    get_destinations_for_piece(game, a2);

    REQUIRE(a2_ptr == board[a2].get());
    REQUIRE(!a2_ptr->has_moved());
    REQUIRE(a3_ptr == board[a3].get());
    REQUIRE(a4_ptr == board[a4].get());
}

TEST_CASE(
    "Repeated queries on an unchanged board return the same pawn destinations without duplicates"
) {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());

    destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());

    destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("Querying an empty square returns no available moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto moves = game.available_moves_for_piece(a4);

    REQUIRE(moves.empty());
}

TEST_CASE("Querying a position beyond any board edge returns no available moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto moves = game.available_moves_for_piece(chess::Position{-1, 1});

    REQUIRE(moves.empty());

    moves = game.available_moves_for_piece(chess::Position{1, -1});

    REQUIRE(moves.empty());

    moves = game.available_moves_for_piece(chess::Position{8, 1});

    REQUIRE(moves.empty());

    moves = game.available_moves_for_piece(chess::Position{1, 8});

    REQUIRE(moves.empty());
}

TEST_CASE("A white pawn can capture an enemy piece one square diagonally forward") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a7, b3);

    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(!moves.empty());

    auto move = std::ranges::find_if(moves, [](auto &move) { return move->to() == b3; });

    REQUIRE(move != moves.end());

    game.execute_move(**move);

    REQUIRE(!board[a2]);
    REQUIRE(board[b3]->type() == chess::PieceType::Pawn);
    REQUIRE(board[b3]->colour() == chess::Colour::White);
}

TEST_CASE("A white pawn can capture an enemy to its left but not a friendly piece to its right") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a2, c3);
    relocate_piece(board, a7, a3);

    const auto destinations = get_destinations_for_piece(game, b2);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c3) == destinations.end());
}

TEST_CASE("A white pawn can promote by capturing on either diagonal") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a2, b7);

    const auto destinations = get_destinations_for_piece(game, b7);

    REQUIRE(std::ranges::count(destinations, a8) == 4);
    REQUIRE(std::ranges::count(destinations, c8) == 4);

    auto moves = game.available_moves_for_piece(b7);

    REQUIRE(moves.size() == 8);

    auto piece_types = get_piece_types_for_promotion(moves, a8);

    REQUIRE(piece_types.contains(chess::PieceType::Queen));
    REQUIRE(piece_types.contains(chess::PieceType::Rook));
    REQUIRE(piece_types.contains(chess::PieceType::Bishop));
    REQUIRE(piece_types.contains(chess::PieceType::Knight));

    piece_types = get_piece_types_for_promotion(moves, c8);

    REQUIRE(piece_types.contains(chess::PieceType::Queen));
    REQUIRE(piece_types.contains(chess::PieceType::Rook));
    REQUIRE(piece_types.contains(chess::PieceType::Bishop));
    REQUIRE(piece_types.contains(chess::PieceType::Knight));
}

TEST_CASE("Executing a promotion replaces the pawn with the chosen piece") {
    constexpr auto promotion_types = std::array{
        chess::PieceType::Queen,
        chess::PieceType::Rook,
        chess::PieceType::Bishop,
        chess::PieceType::Knight,
    };

    constexpr auto colours = std::array{chess::Colour::White, chess::Colour::Black};

    for (const auto colour : colours) {
        CAPTURE(colour);

        const auto original_square = colour == chess::Colour::White ? a2 : a7;
        const auto from = colour == chess::Colour::White ? b7 : b2;
        const auto destinations =
            colour == chess::Colour::White ? std::array{c8, b8} : std::array{c1, b1};

        for (const auto to : destinations) {
            CAPTURE(to);

            for (const auto piece_type : promotion_types) {
                CAPTURE(piece_type);

                chess::Board board;
                chess::GameState game{colour, board};

                relocate_piece(board, original_square, from);
                if (to.file() == from.file()) clear_piece(board, to);

                const auto moves = game.available_moves_for_piece(from);
                const auto chosen_move =
                    std::ranges::find_if(moves, [piece_type, to](const auto &move) {
                        const auto *promotion =
                            dynamic_cast<const chess::PawnPromotionMove *>(move.get());
                        return promotion &&
                               promotion->to() ==
                               to &&
                               promotion->piece_type() == piece_type;
                    });

                REQUIRE(chosen_move != moves.end());

                game.execute_move(**chosen_move);

                REQUIRE(!board[from]);
                REQUIRE(board[to]);
                REQUIRE(board[to]->type() == piece_type);
                REQUIRE(board[to]->colour() == colour);
                REQUIRE(board[to]->has_moved());
            }
        }
    }
}
