cmake_minimum_required(VERSION 3.10)
project(TrieSearchX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/mongo-cxx-driver/4.0.0/share/cmake")
set(CMAKE_INSTALL_RPATH "/opt/homebrew/Cellar/mongo-cxx-driver/4.0.0/lib")



find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)


include_directories(
    include
    /opt/homebrew/Cellar/mongo-cxx-driver/4.0.0/include/mongocxx/v_noabi
    /opt/homebrew/Cellar/mongo-cxx-driver/4.0.0/include/bsoncxx/v_noabi
)


add_executable(TrieSearchX
    src/main.cpp
    src/Trie.cpp
    src/TrieNode.cpp
    src/MongoConnector.cpp
)

target_link_libraries(TrieSearchX
    mongocxx
    bsoncxx
    /opt/homebrew/Cellar/mongo-cxx-driver/4.0.0/lib/libmongocxx.dylib
   /opt/homebrew/Cellar/mongo-cxx-driver/4.0.0/lib/libbsoncxx.dylib
)


add_executable(benchmark
    scripts/benchmark.cpp
    src/Trie.cpp
    src/TrieNode.cpp
)

target_link_libraries(benchmark
    mongocxx
    bsoncxx
)

