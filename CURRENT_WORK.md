# Current work: pawn promotion chooser

We were implementing the GUI for choosing a promotion piece. This is the active task to resume; see [HANDOVER.md](HANDOVER.md) for tutoring and review preferences. Inspect the current files and Git status first.

The chess layer already generates four `PawnPromotionMove` objects (Queen, Rook, Bishop, Knight) for a promotion destination, and executing the chosen move replaces the pawn. `gui::GameController` stores the pending source and destination, opens `PawnPromotionModal`, and later searches the generated moves for the selected piece type.

The modal currently draws four piece choices and a half-square close button. The controller routes mouse release events to `PawnPromotionModal::handle_click()` while it is visible. **Click identification is the unfinished part:** `handle_click()` is still a placeholder that returns Knight for every click. `ModalElement` has an `sf::Rect<float>` intended to hold each choice's clickable bounds, but those rectangles are not yet populated or used. We were discussing storing the drawn bounds and using SFML's `sf::FloatRect::contains` to map a click to a piece choice or to the close control. The controller currently dismisses the modal and clears the pending promotion after any modal click.

Relevant files: `src/gui/modals/pawn_promotion.h`, `src/gui/modals/pawn_promotion.cpp`, and `src/gui/game_controller.cpp`. Also inspect how `elements_` initializes its sprites: it currently dereferences the optional `colour_` before `open()` sets it. Treat that as a current implementation concern to work through with me, not as authorization to change it. No build or GUI run has been performed for this handover.
