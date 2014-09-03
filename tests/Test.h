// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#ifndef TEST_H__
#define TEST_H__

// libc++ and libc
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>


namespace Puzzle15Test
{

class Test
{
public:
    Test(const std::string &exePath, const std::string &testDirName);
    virtual ~Test();

    virtual std::string name() const = 0;

    bool runTest();

private:
    void genFilesList(const std::string &dirName,
                      std::vector<std::string> &filesList);

    virtual std::vector<std::string> outFiles(
                            const std::vector<std::string> &inputFiles,
                            const std::string &dirName) = 0;

    // The genericity of this TDD technique could be taken even further
    // by adding here a virtual (not pure) method which compares the ref
    // files with the output ones and has as default implementation the
    // code wich lays in runTest() after calling outFiles().

    static const std::string relativeTestsDir;
    static const std::string inputDir;
    static const std::string outputDir;
    static const std::string refDir;
    static const std::string refSuffix;

    std::string m_outputPath;

    std::vector<std::string> m_inputFiles;
    std::vector<std::string> m_outputFiles;
    std::vector<std::string> m_refFiles;
};

}

#define TEST_MAIN(BaseClass, TestObject) \
        int main(int argc, char *argv[]) \
        { \
            BaseClass *tester = new TestObject(argc, argv); \
            std::cout << "Test " << tester->name() << " output:" << std::endl; \
            if (!tester->runTest()) \
                std::cout << std::endl << "There were tests which did not " \
                          "pass." << std::endl; \
            else \
                std::cout << std::endl << "Test ended successfully." \
                          << std::endl; \
            delete tester; \
            return 0; \
        }

#endif
