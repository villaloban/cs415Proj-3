#include "TSTtrie.h"

TSTTrie::TSTTrie()
{
    root = nullptr;
    numNodes = 0;
}

TSTTrie::~TSTTrie()
{
    destroy(root);
}

void TSTTrie::insertHelper(Node *&node, const std::string &word, size_t index, long long &ops)
{
    // Implementation goes here
    char ch = word[index];
    if (node == nullptr)
    {
        node = new Node;
        node->ch = ch;
        node->isEnd = false;
        node->left = nullptr;
        node->right = nullptr;
        node->eq = nullptr;
        numNodes++;
    }
    ops++; // Count the operation for the current node comparison
    if (ch < node->ch)
    {
        insertHelper(node->left, word, index, ops);
    }
    else if (ch > node->ch)
    {
        insertHelper(node->right, word, index, ops);
    }
    else
    {
        if (index == word.size() - 1)
        {
            node->isEnd = true;
        }
        else
        {
            insertHelper(node->eq, word, index + 1, ops);
        }
    }
}

void TSTTrie::insert(const std::string &word, long long &ops)
{
    // Implementation goes here
    if (!word.empty())
        insertHelper(root, word, 0, ops);
}

const TSTTrie::Node *TSTTrie::findHelper(const Node *node, const std::string &key, size_t index, long long &ops) const
{
    // Implementation goes here
    if (!node)
    {
        return nullptr;
    }
    char ch = key[index];
    ops++; // Count the operation for the current node comparison
    if (ch < node->ch)
    {
        return findHelper(node->left, key, index, ops);
    }
    else if (ch > node->ch)
    {
        return findHelper(node->right, key, index, ops);
    }
    else
    {
        if (index == key.size() - 1)
        {
            return node;
        }
        else
        {
            return findHelper(node->eq, key, index + 1, ops);
        }
    }
}

bool TSTTrie::search(const std::string &key, long long &ops) const
{
    // Implementation goes here
    const Node *node = findNode(key, ops);
    return node != nullptr && node->isEnd;
}

std::vector<std::string> TSTTrie::autocomplete(const std::string &prefix,
                                               long long &searchOps,
                                               long long &traverseOps) const
{
    std::vector<std::string> out;
    const Node *node = findNode(prefix, searchOps);
    if (node == nullptr)
        return out;

    if (node->isEnd)
        out.push_back(prefix);
    std::string current = prefix;
    collect(node->eq, current, out, traverseOps);
    return out;
}

const TSTTrie::Node *TSTTrie::findNode(const std::string &key, long long &ops) const
{
    // Implementation goes here
    if (key.empty())
        return nullptr;
    return findHelper(root, key, 0, ops);
}

long long TSTTrie::nodeCount() const
{
    return numNodes;
}

long long TSTTrie::spaceUnits() const
{
    return 3 * numNodes; // left, right and mid/equal pointer
}

void TSTTrie::collect(const Node *n, std::string &current,
                      std::vector<std::string> &out, long long &ops) const
{
    if (n == nullptr)
        return;
    ops++;
    collect(n->left, current, out, ops);
    current.push_back(n->ch);
    if (n->isEnd)
    {
        out.push_back(current);
    }
    collect(n->eq, current, out, ops);
    current.pop_back();
    collect(n->right, current, out, ops);
}

void TSTTrie::destroy(Node *n)
{
    if (n == nullptr)
        return;
    destroy(n->left);
    destroy(n->eq); // Destroy the equal branch
    destroy(n->right);
    delete n;
    numNodes--;
}