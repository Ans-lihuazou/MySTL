cmake_minimum_required(VERSION 3.10)

project(MySTL)

add_subdirectory(String)
add_subdirectory(TrieTree)

set(SOURCE_FILE MAIN.cpp ${STRING_SOURCE} ${TRIE_TREE_SOURCE})

add_executable(MySTL ${SOURCE_FILE})
