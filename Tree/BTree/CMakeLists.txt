cmake_minimum_required(VERSION 3.18)

project(BTree)

set(CXX_STANDARD 17)

# create a static library of BTree
add_library(
    btree
    BTree.cc
)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME} btree)
