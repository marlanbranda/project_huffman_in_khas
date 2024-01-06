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


class hekWriter {
    std::ofstream FILE;

    int width;
    int height;
    char padding_byte; // this byte will be helpful if the last byte is padded

    char** encoding_matrix;
    char* data_stream;

    hekWriter();

    void write_file(std::string filename);
    void write_metadata();
    void write_basic_metadata();
    void write_encoding_metadata();
    void write_data(); // TODO TOP PRIORITY

};


#endif //PROJECT_HUFFMAN_IN_KHAS_HEKWRITER_H
