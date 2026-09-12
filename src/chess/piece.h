#pragma once

#include "colour.h"
#include <string_view>

namespace chess {

class Piece {
  public:
    std::string_view icon() const;
    Colour colour() const;

  protected:
    // protected prevents creation of random pieces outside of classes that inherit
    Piece(std::string_view icon, Colour colour);

  private:
    // private prevents us from writing to these variables
    std::string_view icon_;
    Colour colour_;
};

}
