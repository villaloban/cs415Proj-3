
#include <vector>
#include <string>
#include "Normalizer.h"
#include <iostream>
#include "StandardTrie.h"
#include "TSTtrie.h"
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <flag>" << std::endl;
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

    StandardTrie Trie;
    TSTTrie tstTrie;
    long long standardBuildOps = 0;
    long long tstBuildOps = 0;

    for (size_t i = 0; i < words.size(); ++i)
    {
        Trie.insert(words[i], standardBuildOps);
        tstTrie.insert(words[i], tstBuildOps);
    }

    std::cout << "Time taken to build the standard Trie is " << standardBuildOps << " operations and space occupied by it is " << Trie.spaceUnits() << " pointer units" << std::endl;
    std::cout << "Time taken to build the BST based Trie is " << tstBuildOps << " operations and space occupied by it is " << tstTrie.spaceUnits() << " pointer units" << std::endl;
    std::cout << std::endl;

    if (flag == "1")
    {
        std::string query;
        while (true)
        {
            std::cout << "Enter search string: ";
            std::cin >> query;
            query = normalize(query);

            long long standardSearchOps = 0;
            long long tstSearchOps = 0;
            Trie.search(query, standardSearchOps);
            std::cout << "Time taken to search in the standard Trie is " << standardSearchOps << " operations" << std::endl;

            long long auto_completeOps = 0;
            long long traverseOps = 0;

            std::vector<std::string> standardResults = Trie.autocomplete(query, auto_completeOps, traverseOps);

            std::cout << "Auto-complete results using standard Trie are: ";
            for (int i = 0; i < standardResults.size(); ++i)
            {
                if (i > 0)
                {
                    std::cout << ", ";
                }
                std::cout << standardResults[i];
            }
            std::cout << std::endl;
            std::cout << "Time taken to find auto-complete results in the standard Trie is " << auto_completeOps + traverseOps << " operations" << std::endl;
            std::cout << std::endl;
            tstTrie.search(query, tstSearchOps);
            std::cout << "Time taken to search in the BST based Trie is " << tstSearchOps << " operations" << std::endl;

            auto_completeOps = 0;
            traverseOps = 0;
            std::vector<std::string> tstResults = tstTrie.autocomplete(query, auto_completeOps, traverseOps);
            std::cout << "Auto-complete results using BST based Trie are: ";
            for (int i = 0; i < tstResults.size(); ++i)
            {
                if (i > 0)
                {
                    std::cout << ", ";
                }
                std::cout << tstResults[i];
            }
            std::cout << std::endl;
            std::cout << "Time taken to find auto-complete results in the BST based Trie is " << auto_completeOps + traverseOps << " operations" << std::endl;
            std::cout << std::endl;
        }
    }
    else if (flag == "2")
    {
        long long standardSearchOps = 0;
        long long tstSearchOps = 0;
        for (int i = 0; i < words.size(); ++i)
        {
            Trie.search(words[i], standardSearchOps);
            tstTrie.search(words[i], tstSearchOps);
        }
        std::cout << "Time taken to search all the strings in the standard Trie is " << standardSearchOps << " operations" << std::endl;
        std::cout << "Time taken to search all the strings in the BST based Trie is " << tstSearchOps << " operations" << std::endl;
    }
    else
    {
        std::cerr << "Error: Invalid flag." << std::endl;
        return 1;
    }

    return 0;
}