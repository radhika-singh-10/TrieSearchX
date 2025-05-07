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
        std::string word = doc["word"].get_utf8().value.to_string(); //doc["word"].get_utf8().value.to_string();
        trie.insert(word);
    }

    std::cout << "[INFO] Loaded words from MongoDB.\n";
}
