#include "gui/modals/modal.h"

namespace gui {

Modal::Modal()
    : is_visible_{false} {
}

bool Modal::is_visible() const {
    return is_visible_;
}

void Modal::toggle() {
    is_visible_ = !is_visible_;
}

void Modal::show() {
    is_visible_ = true;
}

void Modal::hide() {
    is_visible_ = false;
}

}
