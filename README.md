# TrieSearchX


### TrieSearchX is a blazing-fast autocomplete search system designed using C++ and Cassandra to provide real-time suggestions in under 10ms. It leverages an in-memory Trie structure for instant lookups and a distributed Cassandra database for scalability, ensuring efficient and accurate search results even with millions of queries.

## 🚀 Key Features

✔ Ultra-Fast Search (<10ms Response Time) – Trie-based prefix lookups ensure near-instant autocomplete suggestions.

✔ Scalable Backend with Cassandra – Handles large-scale datasets efficiently with distributed storage.

✔ Adaptive Learning – Logs user queries in Cassandra to improve future search accuracy.

✔ Cache-Optimized Trie – Frequently searched words are cached to minimize database lookups.

✔ Parallel Query Execution – Uses multi-threading for handling large volumes of concurrent searches.
