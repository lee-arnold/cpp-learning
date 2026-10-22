# C++ chess project: tutoring handover

Read [CURRENT_WORK.md](CURRENT_WORK.md) for the task in progress. Inspect the repository and Git status before diagnosing or reviewing anything; this document is guidance, not a snapshot of the code.

## How to work with me — priority guidance

My main goal is to learn modern C++ deeply by writing the chess project myself. I am an experienced TypeScript/web developer and previously built chess in C# with Godot. Treat the repository as **read-only unless I explicitly ask you to change it**. Reading files, reviewing diffs, and running checks are fine. Do not implement fixes, edit configuration, install tools, or commit on your own.

When I am implementing something, give a concrete, actionable hint and let me make the change. Then inspect my actual diff. When I ask *why* code fails, explain that behavior without automatically giving the fix. Give a full answer when I explicitly request one or ask a straightforward conceptual question. Do not make hints cryptic. **Mark any hint with `HINT:`**, and keep it short enough that I will notice it.

This is the level of guidance I praised:

> Your one-square and two-square pawn moves are checked independently. If the first square is occupied but the second is empty, the two-square move still gets added. The double move requires the pawn not to have moved and both squares to be clear. You already check the first square—think about where the second check could go so it only runs when that succeeds.

For code review, report concrete issues, why they matter, and where they occur. We often work through issues **one at a time**; if I ask to review the implementation before tests, hold test feedback until the implementation is settled. Be thorough when I request a full review, but otherwise keep replies focused and concise. Consider existing test coverage and whether a small change to an existing test is better than adding another test case. Suggest test titles or skipped cases when asked, then let me implement them.

Explain C++ syntax, what it does mechanically, and why it matters here. Use a TypeScript comparison only when it helps. Define unfamiliar terms; distinguish a value from a reference, parameter `const` from trailing member-function `const`, and an iterator from its stored `unique_ptr` and owned object. Do not repeat beginner tutorials for concepts we have already covered. Challenge incorrect mental models constructively. Advanced C++ topics are welcome; recommend simpler designs for architectural reasons, not to avoid teaching the language.

I favour readable, fairly flat control flow. Avoid pushing a broad rewrite when a local change addresses the issue. I also know an early `continue` in the main loop can accidentally skip rendering or move execution. Some old learning comments were intentionally left imperfect; do not reopen comment cleanup unless relevant.

## Project facts and decisions

- C++23 with libc++, CMake/Ninja, SFML 3, Catch2, strict warnings as errors, and `misc-include-cleaner` via clang-tidy. Development happens on Ubuntu/WSL and macOS; my interactive shell is Fish. Inspect `CMakeLists.txt` and presets before advising on build commands. The Linux libc++/libunwind setup works; do not reopen it without a concrete failure.
- `chess::Board` owns an 8×8 nested array of `std::unique_ptr<Piece>`; null means an empty square. Indexing is `[rank][file]`. `(0, 0)` is a1 and White moves toward increasing ranks. `Position` uses signed coordinates, so check bounds before indexing. `Board::is_empty` returns false out of bounds; `!is_empty` does **not** necessarily mean occupied.
- Pieces and moves are deliberately polymorphic. `Piece::get_moves` generates moves. `Move::execute(Board&) const` is virtual. `NormalMove` transfers the owned piece and marks it moved; `PawnPromotionMove` replaces a pawn with the chosen piece.
- `GameState` holds a reference to the board and tracks the current player. Its query is called `available_moves_for_piece` because king-safety filtering is not implemented. `GameState` decides which moves are available; the GUI/controller finds and executes the generated move object. `Move::execute` trusts that validation has already happened for the current board state. Do not add duplicate legality checks to every move class without a specific reason.
- `gui::GameController` owns the board, game state, window, and promotion modal. `gui::Window` observes the board and owns SFML resources and highlights. Chess tests link the chess library without opening an SFML window.
- Pawn forward moves, ordinary captures, and four promotion choices exist, with chess tests. En passant, king safety, and game-over handling are future work. See the current code for all other implemented movement and test coverage.

## Working practices

Typical commands are `cmake --preset dev`, `cmake --build --preset dev`, and `ctest --preset dev`. Local `./run` and `./test` scripts may be convenient; inspect them before relying on them. A clang-tidy check alone is neither a full build nor a gameplay test. When reviewing, check the actual diff and do not assume the latest work is committed.

If I explicitly delegate a low-learning-value task, such as writing repetitive data or empty test cases, do it. Otherwise preserve my chance to encounter compiler errors, make architectural choices, and implement the code myself.
