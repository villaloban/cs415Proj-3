
#include <vector>
#include <string>
#include "Normalizer.h"
#include <iostream>
#include "StandardTrie.h"
#include "TSTtrie.h"

void BuildTrie(const std::vector<std::string> &words)
{
    StandardTrie trie;
    TSTTrie tstTrie;
}

void runCase1(const std::vector<std::string> &words) // build, then prompt loop
{
}
void runCase2(const std::vector<std::string> &words) // build, then search every word
{
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    std::string inputFile = argv[1];
    if (inputFile.empty())
    {
        std::cerr << "Error: Input file is empty" << std::endl;
        return 1;
    }
    std::string flag = argv[2];
    if (flag.empty())
    {
        std::cerr << "Error: Flag is empty" << std::endl;
        return 1;
    }

    std::vector<std::string> words = readWords(inputFile);

    if (flag == "case1")
    {
        runCase1(words);
    }
    else if (flag == "case2")
    {
        runCase2(words);
    }
    else
    {
        std::cerr << "Error: Unknown flag" << std::endl;
        return 1;
    }
    return 0;
}