/*
 *  naming comes from:
 *
 *    H    E    K
 *    u    m    i
 *    f    r    z
 *    f    e    i
 *    m         l
 *    a         i
 *    n         r
 *    n         m
 *              a
 *              k
 *
 */


#ifndef PROJECT_HUFFMAN_IN_KHAS_HEKWRITER_H
#define PROJECT_HUFFMAN_IN_KHAS_HEKWRITER_H

#include "treeNode.h"

#include <fstream>
#include <bitset>


class hekWriter {
public:
    std::string filename;

    int width;
    int height;
    // maxgray 255
    char padding_byte; // this byte will be helpful if the last byte is padded

    char** encoding_matrix;
    char* data_stream;

    hekWriter(std::string& filename,
              short int width,
              short int height,
              short int len_of_encoding,
              encoding_struct* encoding_matrix,
              int data_size,
              char* data_stream);

    void write_file();
    void write_metadata();
    void write_basic_metadata();
    void write_encoding_metadata();
    void write_data(); // TODO TOP PRIORITY

};


#endif //PROJECT_HUFFMAN_IN_KHAS_HEKWRITER_H
