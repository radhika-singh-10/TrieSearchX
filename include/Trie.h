#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, std::string prefix, std::vector<std::string>& results);

public:
    Trie();
    void insert(const std::string& word);
    std::vector<std::string> autocomplete(const std::string& prefix);
};

#endif
