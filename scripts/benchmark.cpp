#include "../include/Trie.h"
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

int main() {
    Trie trie;

    // Simulate loading words into the Trie
    vector<string> words = {
        "search", "season", "seal", "see", "seem", "seen",
        "select", "self", "sell", "semantic", "seminar",
        "senior", "sense", "sensor", "sent", "send"
    };

    for (const auto& word : words)
        trie.insert(word);

    vector<string> testQueries = {"se", "sea", "sem", "sel", "sen"};

    cout << "Benchmarking Trie autocomplete...\n";

    for (const auto& query : testQueries) {
        auto start = high_resolution_clock::now();
        auto results = trie.autocomplete(query);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start).count();

        cout << "Query: \"" << query << "\" | Time: " << duration << " μs | Results: ";
        for (const auto& r : results)
            cout << r << " ";
        cout << "\n";

        if (duration > 10000)
            cout << "Failure: Response took more than 10ms!\n";
    }

    return 0;
}
