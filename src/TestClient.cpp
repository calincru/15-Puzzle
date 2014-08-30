// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#include "Board.h"
#include "Solver.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>

using namespace Puzzle8;


int main(int argc, char **args)
{
    if (argc != 2) {
        std::cerr << "The program takes as single argument the input file!\n";
        return 1;
    }

    std::ifstream in(args[1]);
    std::vector<int> blocks;
    int N;

    in >> N;
    blocks.reserve(N);
    for (int i = 0; i < N*N; ++i) {
        int val;
        in >> val;
        blocks.push_back(val);
    }

#ifdef DEBUG
    for (std::vector<int>::const_iterator it = blocks.cbegin();
         it != blocks.cend(); ++it) {
        std::cout << *it;
        if ((it - blocks.cbegin() + 1) % N == 0)
            std::cout << "\n";
        else
            std::cout << " ";
    }
#endif

    Board *initialBoard = new Board(blocks, N);
    assert(initialBoard->isGoal());
    Solver *solver = new Solver(initialBoard);

    if (!solver->isSolvable()) {
        std::cout << "No solution possible\n";
    } else {
        std::cout << "Minimum number of moves: " << solver->moves() << "\n";
        Queue<Board> solution = solver->solution();
        while (!solution.isEmpty()) {
            Board current = solution.dequeue();
            std::cout << current.toString() << "\n";
        }
    }

    delete solver;
    return 0;
}
