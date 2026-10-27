#include "gui/modals/modal.h"

namespace gui {

Modal::Modal()
    : is_visible_{false} {
}

bool Modal::is_visible() {
    return is_visible_;
}

void Modal::toggle() {
    is_visible_ = !is_visible_;
}

}
