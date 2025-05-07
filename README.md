# TrieSearchX


### TrieSearchX is a blazing-fast autocomplete search system designed using C++ and MongoDB to provide real-time suggestions in under 10ms. It leverages an in-memory Trie structure for instant lookups and a distributed MongoDB database for scalability, ensuring efficient and accurate search results even with millions of queries.

##  Key Features

✔ Ultra-Fast Search (<10ms Response Time) – Trie-based prefix lookups ensure near-instant autocomplete suggestions.

✔ Scalable Backend with **MongoDB** – Handles large-scale datasets efficiently with distributed storage.

✔ Adaptive Learning – Logs user queries in Cassandra to improve future search accuracy.

✔ Cache-Optimized Trie – Frequently searched words are cached to minimize database lookups.

✔ Parallel Query Execution – Uses multi-threading for handling large volumes of concurrent searches.

---

## 📦 Prerequisites

- Docker & Docker Compose
- C++17 Compiler (GCC/Clang)
- CMake >= 3.10
- MongoDB C++ Driver (`mongocxx` and `bsoncxx`)
- Python 3 with `pymongo`

---

## Steps to run the application

### ✅ Step 1: Start MongoDB in Docker

```bash
docker compose up -d
```

MongoDB will be available on `localhost:27017` with:
- Username: `root`
- Password: `password`

---

### ✅ Step 2: Seed MongoDB with Sample Words

Install dependencies:
```bash
pip install pymongo
```

Run the Python seeder:
```bash
python scripts/data_loader.py
```

---

### ✅ Step 3: Build the C++ Application

```bash
rm -rf build
mkdir build && cd build
cmake ..
make
```

---

### ✅ Step 4: Run the Application

```bash
./TrieSearchX
```

Type a prefix to search:
```
Search> sem
semantic
seminar
```

To quit:
```
Search> exit
```

---

### ✅ Optional: Run Benchmark

```bash
./benchmark
```

---

---

## ✅ Notes

- MongoDB URI is configured as: `mongodb://root:password@localhost:27017/?authSource=admin`
- Modify `init.js` or `data_loader.py` to seed different words
- Uses `libmongocxx.dylib` and `libbsoncxx.dylib` from Homebrew on macOS

---


