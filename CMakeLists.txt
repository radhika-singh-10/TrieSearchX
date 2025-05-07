cmake_minimum_required(VERSION 3.10)
project(TrieSearchX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Homebrew MongoDB C++ driver paths
set(MONGO_CXX_ROOT "/opt/homebrew/Cellar/mongo-cxx-driver/4.0.0")

set(CMAKE_PREFIX_PATH "${MONGO_CXX_ROOT}/share/cmake")
set(CMAKE_INSTALL_RPATH "${MONGO_CXX_ROOT}/lib")

# Manually set includes
include_directories(
    include
    ${MONGO_CXX_ROOT}/include/mongocxx/v_noabi
    ${MONGO_CXX_ROOT}/include/bsoncxx/v_noabi
)

# === Main App ===
add_executable(TrieSearchX
    src/main.cpp
    src/Trie.cpp
    src/TrieNode.cpp
    src/MongoConnector.cpp
)

target_link_libraries(TrieSearchX
    ${MONGO_CXX_ROOT}/lib/libmongocxx.dylib
    ${MONGO_CXX_ROOT}/lib/libbsoncxx.dylib
)

# === Benchmark ===
add_executable(benchmark
    scripts/benchmark.cpp
    src/Trie.cpp
    src/TrieNode.cpp
)

target_link_libraries(benchmark
    ${MONGO_CXX_ROOT}/lib/libmongocxx.dylib
    ${MONGO_CXX_ROOT}/lib/libbsoncxx.dylib
)
