// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//


// Project Specific
#include "Solver.h"
#include "Board.h"
#include "MinHeap.h"
#include "Queue.h"
#include "Puzzle15Macros.h"

// libc++ and libc
#include <iostream>


namespace Puzzle15
{

Solver::Solver(Board *initial)
{
    // TODO
    UNUSED(initial);
}

Solver::~Solver()
{
    // TODO
}

bool Solver::isSolvable() const
{
    // TODO
    return false;
}

int Solver::moves() const
{
    // TODO
    return -1;
}

Queue<Board> Solver::solution()
{
    // TODO
    return Queue<Board>();
}

}
