#pragma once

#include "chess/moves/move_type.h"
#include "chess/position.h"

namespace chess {

class Board;

class Move {
  public:
    MoveType type() const;
    Position from() const;
    Position to() const;

    // virtual keyword ensures destruction includes the derived object and =0 means we have to
    // override this or c++ complains
    virtual void execute(Board &board) const = 0;
    // this is a desctructor. because we're using Move indirectly (e.g. via Normal), we need to tell
    // the compiler what to do with the polymorphs when the move is deleted
    // =default tells it to use the default destructor behaviour, i.e. when a move is deleted, the
    // polymorph is too
    virtual ~Move() = default;

  protected:
    Move(MoveType type, Position from, Position to);

  private:
    MoveType type_;
    Position from_;
    Position to_;
};

}
