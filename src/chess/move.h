#pragma once

#include "chess/board.h"
#include "move_type.h"
#include "position.h"

namespace chess {

class Move {
  public:
    MoveType type() const;
    Position from() const;
    Position to() const;
    bool is_legal() const;

    // virtual keyword and =0 means we have to override this or c++ complains
    // we want a refernce to the board rather than a copy. it's all unique pointers anyway
    virtual void execute(Board &board) const = 0;
    // this is a desctructor. because we're using Move indirectly (e.g. via Normal), we need to tell
    // the compiler what to do with the polymorphs when the move is deleted
    // this tells it to use the default behaviour, i.e. when a move is deleted, the polymorph is too
    virtual ~Move() = default;

  protected:
    Move(MoveType type, Position from, Position to);

  private:
    MoveType type_;
    Position from_;
    Position to_;
};

}
