#ifndef BSTTRIE_H
#define BSTTRIE_H

#include <string>
#include <vector>

// BSTTrie.h
class BSTTrie
{
public:
    // same public interface as StandardTrie; spaceUnits() is 2 * nodeCount

private:
    struct Node
    {
        char ch;
        bool isEnd;
        Node *left, *right;
    };
    Node *root; // nullptr until first insert
    long long numNodes;

    const Node *findNode(const std::string &key, long long &ops) const;
    void collect(const Node *n, std::string &current,
                 std::vector<std::string> &out, long long &ops) const;
    void destroy(Node *n);
};

#endif // BSTTRIE_H