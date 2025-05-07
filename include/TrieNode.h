#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>
#include <string>
#include <vector>

class TrieNode {
public:
    bool isEndOfWord;
    std::unordered_map<char, TrieNode*> children;

    TrieNode();
};

#endif
