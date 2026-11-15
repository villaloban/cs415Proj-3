#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <string>
#include <vector>
#include <fstream>

// Normalizer.h
std::string normalize(const std::string &raw);                   // lowercase, keep a-z only
std::vector<std::string> readWords(const std::string &filename); // skips tokens that clean to ""

#endif // NORMALIZER_H