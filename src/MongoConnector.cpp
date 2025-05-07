#include "../include/MongoConnector.h"
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>

void MongoConnector::loadWordsToTrie(Trie& trie) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://root:password@localhost:27017/"}};
    auto collection = conn["trie_db"]["words"];

    for (auto&& doc : collection.find({})) {
        auto element = doc["word"];
        if (element.type() == bsoncxx::type::k_utf8) {
            std::string word = element.get_string().value.to_string();
            trie.insert(word);
        }
    }

    std::cout << "[INFO] Loaded words from MongoDB.\n";
}
