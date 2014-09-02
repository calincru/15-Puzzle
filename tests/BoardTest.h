// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#ifndef BOARDTEST_H__
#define BOARDTEST_H__

// Project specific
#include "Test.h"

// libc++ and libc
#include <fstream>
#include <iostream>


namespace Puzzle15
{
    class Board;
}

namespace Puzzle15Test
{

class BoardTest : public Test
{
public:
    BoardTest(int argc, char **argv);
    virtual ~BoardTest();

    virtual std::string name() const;

private:
    virtual std::vector<std::string> outFiles(
                            const std::vector<std::string> &inputFiles,
                            const std::string &dirName);

    void printBoardMatrix(const Puzzle15::Board &board, int dim,
                          std::ofstream &out);

    static const std::string dirName;
    static const std::string outSuffix;
};

}

#endif
