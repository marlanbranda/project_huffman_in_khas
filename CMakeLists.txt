cmake_minimum_required(VERSION 3.27)
project(project_huffman_in_khas)

set(CMAKE_CXX_STANDARD 14)

add_executable(dev_process
        code/main.cpp
        code/treeNode.cpp
        code/header_files/treeNode.h
        code/pgmReader.cpp
        code/header_files/pgmReader.h
        code/miscellaneous.cpp
        code/header_files/miscellaneous.h
        code/tests.cpp
        code/header_files/tests.h
        code/freqTable.cpp
        code/header_files/freqTable.h
        code/hekWriter.cpp
        code/header_files/hekWriter.h
        code/hekReader.cpp
        code/header_files/hekReader.h
        code/header_files/pgmWriter.h
        code/pgmWriter.cpp
)
