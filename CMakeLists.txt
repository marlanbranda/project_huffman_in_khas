cmake_minimum_required(VERSION 3.27)
project(project_huffman_in_khas)

set(CMAKE_CXX_STANDARD 14)

add_executable(dev_process
        code/main.cpp
        achieving_tree.cpp
        code/huffman_node.cpp
        code/huffman_node.h
        )
