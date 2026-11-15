#ifndef STANDARDTRIE_H
#define STANDARDTRIE_H

#include <string>
#include <vector>

// StandardTrie.h
class StandardTrie
{
public:
    StandardTrie();
    ~StandardTrie();

    void insert(const std::string &word, long long &ops);
    bool search(const std::string &key, long long &ops) const;
    std::vector<std::string> autocomplete(const std::string &prefix,
                                          long long &searchOps,
                                          long long &traverseOps) const;
    long long nodeCount() const;
    long long spaceUnits() const; // 26 * nodeCount

private:
    struct Node
    {
        Node *children[26];
        bool isEnd;
    };
    Node *root;
    long long numNodes; // includes root

    const Node *findNode(const std::string &key, long long &ops) const;
    void collect(const Node *n, std::string &current,
                 std::vector<std::string> &out, long long &ops) const;
    void destroy(Node *n);
    void countNodes(const Node *node, long long &count) const;
};

#endif // STANDARDTRIE_H