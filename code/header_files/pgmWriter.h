#ifndef PROJECT_HUFFMAN_IN_KHAS_PGMWRITER_H
#define PROJECT_HUFFMAN_IN_KHAS_PGMWRITER_H

#include <string>
#include <fstream>

#include "hekReader.h"

class pgmWriter
{
public:
    std::string filename;
    int width;
    int height;
    int max_gray;
    long long int pgm_file_size;

    pgmWriter(hekReader* hekReaderObj, std::string filename);

};


#endif //PROJECT_HUFFMAN_IN_KHAS_PGMWRITER_H
