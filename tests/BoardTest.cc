// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

// Project specific
#include "BoardTest.h"
#include "Board.h"
#include "Puzzle15Macros.h"

// libc++ and libc
#include <list>


namespace Puzzle15Test
{

const std::string BoardTest::dirName = "/boardtest";
const std::string BoardTest::outSuffix = "_out";

BoardTest::BoardTest(int argc, char **argv)
    : Test(argv[0], dirName)
{
    if (argc != 1)
        std::cout << "Warning: This test takes no arguments. All argumets "
                     "will be ignored." << std::endl;
}

BoardTest::~BoardTest()
{
    // nothing to do
}

std::string BoardTest::name() const
{
    return "BoardTest";
}

std::vector<std::string> BoardTest::outFiles(
                const std::vector<std::string> &inputFiles,
                const std::string &dirName)
{
    std::vector<std::string> outFiles;

    for (std::vector<std::string>::const_iterator it = inputFiles.cbegin();
         it != inputFiles.cend(); ++it) {
        // first read the input file and initialize the Board.
        std::ifstream in(*it);
        int N;
        std::vector<int> blocks;

        in >> N;
        for (int i = 0; i < N * N; ++i) {
            int val;
            in >> val;
            blocks.push_back(val);
        }
        in.close();
        Puzzle15::Board *board = new Puzzle15::Board(blocks, N);

        // then use the board object to generate the output file.
        const std::string outFile = dirName + std::string("/") +
                                    it->substr(it->find_last_of("/") + 1) +
                                    outSuffix;
        outFiles.push_back(outFile);
        std::ofstream out(outFile);

        // dimension
        out << board->dimension() << std::endl;

        // empty position
        int emptyRow, emptyColumn;
        board->emptyPosition(emptyRow, emptyColumn);
        out << emptyRow << " " << emptyColumn << std::endl;

        // hamming priority
        out << board->hamming() << std::endl;

        // manhattan priority
        out << board->manhattan() << std::endl;

        // is goal board?
        out << (board->isGoal() ? "1" : "0") << std::endl;

        // upper neighbour
        printBoardMatrix(board->upperNeighbour(emptyRow, emptyColumn), N, out);
        // lower neighbour
        printBoardMatrix(board->lowerNeighbour(emptyRow, emptyColumn), N, out);
        // left neighbour
        printBoardMatrix(board->leftNeighbour(emptyRow, emptyColumn), N, out);
        // right neighbour
        printBoardMatrix(board->rightNeighbour(emptyRow, emptyColumn), N, out);

        out.close();
        delete board;
    }

    return outFiles;
}

void BoardTest::printBoardMatrix(const Puzzle15::Board &board, int dim,
                                 std::ofstream &out)
{
    for (std::vector<int>::const_iterator it = board.m_blocks.cbegin();
         it != board.m_blocks.cend(); ++it) {
        int i = (it - board.m_blocks.cbegin())/dim;
        int j = it - board.m_blocks.cbegin() - i*dim;

        out << *it;
        if (j < dim - 1)
            out << " ";
        else
            out << "\n";
    }
}

}

TEST_MAIN(Puzzle15Test::Test, Puzzle15Test::BoardTest);
