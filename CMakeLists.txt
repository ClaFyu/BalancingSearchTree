cmake_minimum_required(VERSION 3.14)
project(ST)

set(CMAKE_CXX_STANDARD 14)

add_executable(ST main.cpp sources/AVL.cpp headers/AVL.h headers/BTree.h sources/BTree.cpp headers/BPTree.h sources/BPTree.cpp headers/RBTree.h sources/RBTree.cpp)