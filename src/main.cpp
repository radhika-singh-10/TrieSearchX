#include "../include/Trie.h"
#include "../include/MongoConnector.h"
#include <iostream>

int main() {
    Trie trie;
    MongoConnector loader;
    loader.loadWordsToTrie(trie);

    std::string input;
    while (true) {
        std::cout << "Search> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        auto results = trie.autocomplete(input);
        for (const auto& word : results)
            std::cout << "  " << word << "\n";
    }

    return 0;
}
