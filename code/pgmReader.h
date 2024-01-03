#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>


#ifndef PROJECT_HUFFMAN_IN_KHAS_PGMREADER_H
#define PROJECT_HUFFMAN_IN_KHAS_PGMREADER_H


class pgmReader {
public:
    std::string filename;
    int width;
    int height;
    int max_gray;
    std::streampos data;
    int data_size;

    pgmReader(const std::string& filename); // NOLINT(*-explicit-constructor)
    ~pgmReader();

    char* data_as_array() const;

};


#endif //PROJECT_HUFFMAN_IN_KHAS_PGMREADER_H
