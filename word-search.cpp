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

private:
    TrieNode* root;

public:
    Trie() { 
        root = new TrieNode(); 
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
            node->suggestions.push_back(word);
        }
        node->isEndOfWord = true;
    }

    vector<string> search(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return {};  
            }
            node = node->children[ch];
        }
        return node->suggestions;
    }
};

// this is connecting to the database with no cache - worst case
// there is one more apporach where connection is done to the cahce, and then the database 
// with the second apporach a batch query is run to get top k prefix in the cache at a gap of every n days
class CassandraDB {
private:
    CassCluster* cluster;
    CassSession* session;

public:
    CassandraDB() {
        cluster = cass_cluster_new();
        session = cass_session_new();
        cass_cluster_set_contact_points(cluster, "127.0.0.1");  
        CassFuture* connect_future = cass_session_connect(session, cluster);
        cass_future_wait(connect_future);
        cass_future_free(connect_future);
    }

    vector<string> getSuggestionsFromDB(const string& prefix) {
        vector<string> results;
        string query = "SELECT words FROM search_suggestions WHERE prefix = '" + prefix + "';";
        CassStatement* statement = cass_statement_new(query.c_str(), 0);
        CassFuture* future = cass_session_execute(session, statement);

        cass_future_wait(future);
        const CassResult* result = cass_future_get_result(future);
        CassIterator* iterator = cass_iterator_from_result(result);

        while (cass_iterator_next(iterator)) {
            const CassRow* row = cass_iterator_get_row(iterator);
            const CassValue* value = cass_row_get_column_by_name(row, "words");
            const char* text;
            size_t text_length;
            cass_value_get_string(value, &text, &text_length);
            results.push_back(string(text, text_length));
        }

        cass_iterator_free(iterator);
        cass_result_free(result);
        cass_statement_free(statement);
        cass_future_free(future);
        return results;
    }

    void insertSuggestionIntoDB(const string& prefix, const vector<string>& words) {
        string query = "INSERT INTO search_suggestions (prefix, words) VALUES ('" + prefix + "', ?);";
        CassStatement* statement = cass_statement_new(query.c_str(), 1);
        CassCollection* collection = cass_collection_new(CASS_COLLECTION_TYPE_LIST, words.size());

        for (const auto& word : words) {
            cass_collection_append_string(collection, word.c_str());
        }

        cass_statement_bind_collection(statement, 0, collection);
        CassFuture* future = cass_session_execute(session, statement);

        cass_future_wait(future);
        cass_future_free(future);
        cass_statement_free(statement);
        cass_collection_free(collection);
    }
};



int main() {
    Trie trie;
    CassandraDB db;
    trie.insert("apple");
    trie.insert("apricot");
    trie.insert("banana");
    trie.insert("bat");
    trie.insert("ball");

    string prefix;
    cout << "Enter search prefix: ";
    cin >> prefix;

    vector<string> suggestions = trie.search(prefix);
    if (suggestions.empty()) {
        cout << "Fetching from Cassandra...\n";
        suggestions = db.getSuggestionsFromDB(prefix);
        for (const string& word : suggestions) {
            trie.insert(word);  
        }
    }

    if (suggestions.empty()) {
        cout << "No suggestions found!\n";
    } else {
        cout << "Suggestions:\n";
        for (const string& word : suggestions) {
            cout << word << endl;
        }
    }

    return 0;
}