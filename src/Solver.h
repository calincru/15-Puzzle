// Copyright (C) 2014 Călin Cruceru
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#ifndef SOLVER_H__
#define SOLVER_H__

// Project Specific
#include "Board.h"


namespace Puzzle8
{

class Solver
{
public:
    Solver(Board *initial);
    ~Solver();

    bool isSolvable() const;
    int moves() const;
    Queue<Board> solution();

private:

};

}

#endif
