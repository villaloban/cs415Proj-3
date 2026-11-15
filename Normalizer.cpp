#include "Normalizer.h"
// Normalizer.cpp
std::string normalize(const std::string &raw)
{
    std::string result;
    for (int i = 0; i < raw.size(); ++i)
    {
        if (std::isalpha(raw[i]))
        {
            result += std::tolower(raw[i]);
        }
    }
    return result;
}

std::vector<std::string> readWords(const std::string &filename)
{
    std::vector<std::string> words;
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {
        std::string normalized = normalize(word);
        if (!normalized.empty())
        {
            words.push_back(normalized);
        }
    }
    return words;
}