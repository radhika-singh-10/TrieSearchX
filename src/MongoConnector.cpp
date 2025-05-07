#include "../include/MongoConnector.h"
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>

void MongoConnector::loadWordsToTrie(Trie& trie) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://root:password@localhost:27017/?authSource=admin"}};
    auto collection = conn["trie_db"]["words"];

    for (auto&& doc : collection.find({})) {
        auto element = doc["word"];
        if (element.type() == bsoncxx::type::k_string) {
            std::string word = std::string(element.get_string().value);
            trie.insert(word);
        }
    }

    std::cout << "[INFO] Loaded words from MongoDB.\n";
}
