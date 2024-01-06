cmake_minimum_required(VERSION 3.27)
project(project_huffman_in_khas)

set(CMAKE_CXX_STANDARD 14)

add_executable(dev_process
        code/main.cpp
        code/treeNode.cpp
        code/treeNode.h
        code/pgmReader.cpp
        code/pgmReader.h
        code/miscellaneous.cpp
        code/miscellaneous.h
        code/tests.cpp
        code/tests.h
        code/freqTable.cpp
        code/freqTable.h
        code/hekWriter.cpp
        code/hekWriter.h
        code/hekReader.cpp
        code/hekReader.h
)
