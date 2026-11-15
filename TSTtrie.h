#ifndef TSTTRIE_H
#define TSTTRIE_H

#include <string>
#include <vector>

// TSTtrie.h
class TSTTrie
{
public:
    // same public interface as StandardTrie; spaceUnits
    TSTTrie();
    ~TSTTrie();

    void insert(const std::string &word, long long &ops);
    bool search(const std::string &key, long long &ops) const;
    std::vector<std::string> autocomplete(const std::string &prefix,
                                          long long &searchOps,
                                          long long &traverseOps) const;
    long long nodeCount() const;
    long long spaceUnits() const; // 26 * nodeCount() is 2 * nodeCount

private:
    struct Node
    {
        char ch;
        bool isEnd;
        Node *left, *right, *eq;
    };
    Node *root; // nullptr until first insert
    long long numNodes;

    void insertHelper(Node *&node, const std::string &word, size_t index, long long &ops);
    const Node *findHelper(const Node *node, const std::string &key, size_t index, long long &ops) const;
    const Node *findNode(const std::string &key, long long &ops) const;
    void collect(const Node *n, std::string &current,
                 std::vector<std::string> &out, long long &ops) const;
    void destroy(Node *n);
};

#endif // TSTTRIE_H