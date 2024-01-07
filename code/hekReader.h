#ifndef PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H
#define PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H

#include <fstream>

#include "treeNode.h"

class hekReader {
public:
    std::string hek_file_name;
    std::string pgm_file_name;

    char* magic_number; // constant
    int width;
    int height;
    int max_gray; // constant
    char padding_byte; // this byte will be helpful if the last byte is padded

    int encoding_len;
    encoding_struct* encoding_matrix;
    int data_size;
    std::string data_stream;

    hekReader();

    void read_hek(std::string hek_file_name);
//        void read_metadata();
//            void read_basic_metadata();
//            void read_encoding_metadata();
//        void read_data();

    void write_pgm(std::string pgm_file_name);
//        void write_metadata();
//        void write_data();
};


#endif //PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H
