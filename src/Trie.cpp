#include "../include/Trie.h"
#include <queue>

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        if (!current->children[ch])
            current->children[ch] = new TrieNode();
        current = current->children[ch];
    }
    current->isEndOfWord = true;
}

void Trie::dfs(TrieNode* node, std::string prefix, std::vector<std::string>& results) {
    if (node->isEndOfWord) results.push_back(prefix);
    for (auto& [ch, child] : node->children)
        dfs(child, prefix + ch, results);
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    TrieNode* current = root;
    for (char ch : prefix) {
        if (!current->children[ch]) return {};
        current = current->children[ch];
    }
    std::vector<std::string> results;
    dfs(current, prefix, results);
    return results;
}
