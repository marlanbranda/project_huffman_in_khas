cmake_minimum_required(VERSION 3.27)
project(project_huffman_in_khas)

set(CMAKE_CXX_STANDARD 14)

add_executable(dev_process
        code/main.cpp
        code/source_codes/treeNode.cpp
        code/header_files/treeNode.h
        code/source_codes/pgmReader.cpp
        code/header_files/pgmReader.h
        code/source_codes/miscellaneous.cpp
        code/header_files/miscellaneous.h
        code/source_codes/tests.cpp
        code/header_files/tests.h
        code/source_codes/freqTable.cpp
        code/header_files/freqTable.h
        code/source_codes/hekWriter.cpp
        code/header_files/hekWriter.h
        code/source_codes/hekReader.cpp
        code/header_files/hekReader.h
        code/header_files/pgmWriter.h
        code/source_codes/pgmWriter.cpp
)

add_executable(pgm_to_hek_compress
        code/pgm_to_hek_compress.cpp
        code/source_codes/treeNode.cpp
        code/header_files/treeNode.h
        code/source_codes/pgmReader.cpp
        code/header_files/pgmReader.h
        code/source_codes/miscellaneous.cpp
        code/header_files/miscellaneous.h
        code/source_codes/freqTable.cpp
        code/header_files/freqTable.h
        code/source_codes/hekWriter.cpp
        code/header_files/hekWriter.h
        code/source_codes/hekReader.cpp
        code/header_files/hekReader.h
        code/header_files/pgmWriter.h
        code/source_codes/pgmWriter.cpp
)

add_executable(hek_to_pgm_decompress
        code/hek_to_pgm_decompress.cpp
        code/source_codes/treeNode.cpp
        code/header_files/treeNode.h
        code/source_codes/pgmReader.cpp
        code/header_files/pgmReader.h
        code/source_codes/miscellaneous.cpp
        code/header_files/miscellaneous.h
        code/source_codes/freqTable.cpp
        code/header_files/freqTable.h
        code/source_codes/hekWriter.cpp
        code/header_files/hekWriter.h
        code/source_codes/hekReader.cpp
        code/header_files/hekReader.h
        code/header_files/pgmWriter.h
        code/source_codes/pgmWriter.cpp
)
