#pragma once

#include "colour.h"
#include <string_view>

namespace chess {

class Piece {
  public:
    std::string_view icon() const;
    Colour colour() const;

  protected:
    explicit Piece(std::string_view icon, Colour colour);

  private:
    std::string_view icon_;
    Colour colour_;
};
}
