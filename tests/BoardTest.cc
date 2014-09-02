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
    UNUSED(inputFiles);
    UNUSED(dirName);

    std::vector<std::string> outFiles;
    return outFiles;
}


}

TEST_MAIN(Puzzle15Test::Test, Puzzle15Test::BoardTest);
