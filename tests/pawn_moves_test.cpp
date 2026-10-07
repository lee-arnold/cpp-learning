#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/position.h"

#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <memory>
#include <vector>

using namespace test_squares;

TEST_CASE("An unmoved pawn with a clear path can advance one or two squares") {
    const chess::Board board;
    const chess::GameState game{board};

    const auto moves = game.available_moves_for_piece(a2);

    std::vector<chess::Position> destinations;
    for (const auto &move : moves) {
        destinations.push_back(move->to());
    }

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("A previously moved pawn with a clear path can advance only one square") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, a2, a3, true);

    const auto moves = game.available_moves_for_piece(a3);

    std::vector<chess::Position> destinations;
    for (const auto &move : moves) {
        destinations.push_back(move->to());
    }

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("A friendly piece immediately ahead prevents all pawn forward moves") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, b2, a3);

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(moves.empty());
}

TEST_CASE("An enemy piece immediately ahead prevents all pawn forward moves") {
    SKIP("Not implemented yet");
}

TEST_CASE("A friendly piece two squares ahead allows only the one-square pawn advance") {
    SKIP("Not implemented yet");
}

TEST_CASE("An enemy piece two squares ahead allows only the one-square pawn advance") {
    SKIP("Not implemented yet");
}

TEST_CASE("An unmoved white pawn with a clear path advances toward increasing ranks") {
    SKIP("Not implemented yet");
}

TEST_CASE("An unmoved black pawn with a clear path advances toward decreasing ranks") {
    SKIP("Not implemented yet");
}

TEST_CASE("A white pawn on the final rank has no forward moves") {
    SKIP("Not implemented yet");
}

TEST_CASE("A black pawn on the final rank has no forward moves") {
    SKIP("Not implemented yet");
}

TEST_CASE(
    "An unmoved white pawn one rank from the edge has only an in-bounds one-square destination"
) {
    SKIP("Not implemented yet");
}

TEST_CASE(
    "An unmoved black pawn one rank from the edge has only an in-bounds one-square destination"
) {
    SKIP("Not implemented yet");
}

TEST_CASE("Pawns on the a-file and h-file advance without changing files") {
    SKIP("Not implemented yet");
}

TEST_CASE("Every generated pawn move records the queried square as its source") {
    SKIP("Not implemented yet");
}

TEST_CASE("Querying pawn moves leaves the board and the pawn moved-state unchanged") {
    SKIP("Not implemented yet");
}

TEST_CASE(
    "Repeated queries on an unchanged board return the same pawn destinations without duplicates"
) {
    SKIP("Not implemented yet");
}

TEST_CASE("Querying an empty square returns no available moves") {
    SKIP("Not implemented yet");
}

TEST_CASE("Querying a position beyond any board edge returns no available moves") {
    SKIP("Not implemented yet");
}
