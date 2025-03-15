#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassandra.h>  
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    vector<string> suggestions;

    TrieNode() { isEndOfWord = false; }
};

class Trie{

}

class Cassandra{
    
}


int main() {
    Trie trie;
    CassandraDB db;
    return 0;
}