// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

// Project specific
#include "Test.h"
#include "Puzzle15Macros.h"

// libc++ and libc
#include <fstream>
#include <cassert>
#include <sys/stat.h>
#include <dirent.h>


namespace Puzzle15Test
{

static const std::string usage = \
"The directory structure is supposed to be similar to this:\n"
"                    .                               \n"
"                    ├── BoardTest.cc                \n"
"                    ├── BoardTest.h                 \n"
"                    ├── CMakeLists.txt              \n"
"                    ├── Test.cc                     \n"
"                    ├── testfiles                   \n"
"                    │   ├── boardtest               \n"
"                    │   │   ├── input               \n"
"                    │   │   │   └── board1.txt      \n"
"                    │   │   ├── output              \n"
"                    │   │   └── ref                 \n"
"                    │   │       └── board1_ref.txt  \n"
"                    │   ├── README.md               \n"
"                    │   └── solvertest              \n"
"                    │       ├── input               \n"
"                    │       ├── output              \n"
"                    │       └── ref                 \n"
"                    └── Test.h                      \n";

const std::string Test::relativeTestsDir = "/testfiles";
const std::string Test::inputDir = "/input";
const std::string Test::outputDir = "/output";
const std::string Test::refDir = "/ref";
const std::string Test::refSuffix = "_ref";

Test::Test(const std::string &exePath, const std::string &testDirName)
{
    std::string testPath = exePath.substr(0, exePath.find_last_of("/")) +
                           relativeTestsDir + testDirName;

    // Test if test root directory exists. It MUST exist.
    struct stat dirInfo;
    DIE(stat(testPath.c_str(), &dirInfo) || !S_ISDIR(dirInfo.st_mode),
        usage.c_str());

    // Test if input directory exists. It MUST exist.
    std::string fullInputPath = testPath + inputDir;
    DIE(stat(fullInputPath.c_str(), &dirInfo) || !S_ISDIR(dirInfo.st_mode),
        usage.c_str());

    // Test if ref directory exists. It MUST exist;
    std::string fullRefPath = testPath + refDir;
    DIE(stat(fullRefPath.c_str(), &dirInfo) || !S_ISDIR(dirInfo.st_mode),
        usage.c_str());

    // Test if output directory exists. If it does not exist, create it.
    // FIXME: This won't work on windows.
    m_outputPath = testPath + outputDir;
    if (stat(m_outputPath.c_str(), &dirInfo) || !S_ISDIR(dirInfo.st_mode))
        mkdir(m_outputPath.c_str(), 0640);

    // Generate the lists of input/ref files.
    genFilesList(fullInputPath, m_inputFiles);
    genFilesList(fullRefPath, m_refFiles);

    // Check input/ref files consistency
    for (auto &i : m_refFiles) {
        // In the ./ref directory should be only _ref.txt files.
        DIE(i.rfind(refSuffix) == std::string::npos, "An invalid file has been "
                                                     "found in ./ref.");

        // There should be only one input file which has cutName as its name.
        std::string noSuffix = i.substr(0, i.rfind(refSuffix));
        std::string refFile = noSuffix.substr(noSuffix.find_last_of("/") + 1);
        int count = 0;
        for (auto &j : m_inputFiles) {
            std::string inFile = j.substr(j.find_last_of("/") + 1);
            if (inFile == refFile)
                ++count;
        }

        DIE(count != 1, "There should be exactly one file named <file_name> "
                        "in the input directory and one file named "
                        "<file_name_ref in the ref directory.");
    }
}

Test::~Test()
{
    // nothing to do
}

#define TEST_FAILED(number, message) \
        std::cout << "Test " << number << " failed: " << message << std::endl

#define TEST_PASSED(number) \
        std::cout << "Test " << number << " passed successfully." << std::endl

bool Test::runTest()
{
    return compare(outFiles(m_inputFiles, m_outputPath), m_refFiles);
}

void Test::genFilesList(const std::string &dirName,
                        std::vector<std::string> &filesList)
{
    DIR *dir = opendir(dirName.c_str());
    if (!dir)
        return;

    struct dirent *ent = readdir(dir);
    while (ent) {
        if (std::string(ent->d_name) != std::string(".") &&
            std::string(ent->d_name) != std::string("..")) {
            std::string path = dirName + "/" + ent->d_name;
            char buf[PATH_MAX+1];
            realpath(path.c_str(), buf);
            filesList.push_back(buf);
        }
        ent = readdir(dir);
    }

    closedir(dir);
}

bool Test::compare(const std::vector<std::string> &outFiles,
                   const std::vector<std::string> &refFiles) const
{
    std::vector<std::string>::const_iterator refBeg = refFiles.cbegin();
    std::vector<std::string>::const_iterator outBeg = outFiles.cbegin();
    std::vector<std::string>::const_iterator refEnd = refFiles.cend();
    std::vector<std::string>::const_iterator outEnd = outFiles.cend();

    bool passedEntirely = true;
    for (; refBeg != refEnd && outBeg != outEnd; ++refBeg, ++outBeg) {
        std::ifstream refIn(*refBeg);
        std::ifstream outIn(*outBeg);

        int testNr = refBeg - refFiles.cbegin() + 1;
        bool passed = true;
        while (true) {
            int refVal, outVal;
            refIn >> refVal;
            outIn >> outVal;

            if (refIn.eof()) {
                if (!outIn.eof()) {
                    TEST_FAILED(testNr, "Output file contains more items than "
                                        "expected.");
                    passed = false;
                }
                break;
            }

            if (outIn.eof()) {
                if (!refIn.eof()) {
                    TEST_FAILED(testNr, "Ref file contains more items than the "
                                        "output file.");
                    passed = false;
                }
                break;
            }
        }

        if (!passed) {
            TEST_FAILED(testNr, "Values differ.");
            passedEntirely = false;
        } else {
            TEST_PASSED(testNr);
        }

        refIn.close();
        outIn.close();
    }

    return passedEntirely;
}


}
