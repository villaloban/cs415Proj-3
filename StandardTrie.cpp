#include "StandardTrie.h"
// StandardTrie.cpp

StandardTrie::StandardTrie()
{
    // Implementation goes here
    root = new Node();
    root->isEnd = false;
}

StandardTrie::~StandardTrie()
{
    // Implementation goes here
    destroy(root);
    root = nullptr;
}

void StandardTrie::insert(const std::string &word, long long &ops)
{
    // Implementation goes here
    Node *node = root;
    for (int i = 0; i < word.size(); ++i)
    {
        ++ops;
        int index = word[i] - 'a';
        if (node->children[index] == nullptr)
        {
            node->children[index] = new Node();
                }
        node = node->children[index];
    }
    node->isEnd = true;
}

bool StandardTrie::search(const std::string &key, long long &ops) const
{
    // Implementation goes here
    const Node *node = findNode(key, ops);
    if (node == nullptr)
    {
        return false;
    }
    return node->isEnd;
}

void StandardTrie::destroy(Node *node)
{
    // Implementation goes here
    if (node == nullptr)
    {
        return;
    }
    for (int i = 0; i < 26; ++i)
    {
        destroy(node->children[i]);
    }
    delete node;
}

std::vector<std::string> StandardTrie::autocomplete(const std::string &prefix,
                                                    long long &searchOps,
                                                    long long &traverseOps) const
{
    // Implementation goes here
    const Node *node = findNode(prefix, searchOps);
    if (node == nullptr)
    {
        return {};
    }
    std::vector<std::string> out;
    std::string current = prefix;
    collect(node, current, out, traverseOps);
    return out;
}

long long StandardTrie::nodeCount() const
{
    // Implementation goes here
    long long count = 0;
    countNodes(root, count);
    return count;
}

long long StandardTrie::spaceUnits() const
{
    // Implementation goes here
    return nodeCount() * 26;
}

const StandardTrie::Node *StandardTrie::findNode(const std::string &key, long long &ops) const
{
    // Implementation goes here
    const Node *node = root;
    for (int i = 0; i < key.size(); ++i)
    {
        ++ops;
        int index = key[i] - 'a';
        if (node->children[index] == nullptr)
        {
            return nullptr;
        }
        node = node->children[index];
    }
    return node;
}

void StandardTrie::collect(const Node *n, std::string &current,
                           std::vector<std::string> &out, long long &ops) const
{
    // Implementation goes here
    ++ops;
    if (n->isEnd)
    {
        out.push_back(current);
    }
    for (int i = 0; i < 26; ++i)
    {
        if (n->children[i] != nullptr)
        {
            current.push_back('a' + i);
            collect(n->children[i], current, out, ops);
            current.pop_back();
        }
    }
}

void StandardTrie::countNodes(const Node *node, long long &count) const
{
    if (node == nullptr)
    {
        return;
    }
    ++count;
    for (int i = 0; i < 26; ++i)
    {
        countNodes(node->children[i], count);
    }
}
