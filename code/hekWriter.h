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

    char padding_byte; // this byte will be helpful if the last byte is padded


    hekWriter(std::string& filename,
              short int width,
              short int height,
              short int len_of_encoding,
              encoding_struct* encoding_matrix,
              int data_size,
              char* data_stream);

};


#endif //PROJECT_HUFFMAN_IN_KHAS_HEKWRITER_H
