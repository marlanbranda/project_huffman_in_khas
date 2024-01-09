#ifndef PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H
#define PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H

#include <fstream>

#include "treeNode.h"

class hekReader {
public:
    std::string hek_file_name;
    std::string pgm_file_name;

    int width{};
    int height{};
    int max_gray; // constant
    char padding_byte{}; // defunct now

    int encoding_len{};
    encoding_struct* encoding_matrix{};
    int data_size{};
    std::string data_stream;

    hekReader();
    ~hekReader();

    void read_hek(const std::string& hek_file_name);
//        void read_metadata();
//            void read_basic_metadata();
//            void read_encoding_metadata();
//        void read_data();

};


#endif //PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H
