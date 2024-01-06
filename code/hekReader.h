#ifndef PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H
#define PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H

#include <fstream>

class hekReader {
    std::ifstream HEK_FILE;
    std::ofstream PGM_FILE;

    char* magic_number; // constant
    int width;
    int height;
    int max_gray; // constant
    char padding_byte; // this byte will be helpful if the last byte is padded

    char** encoding_matrix;
    char* data_stream;

    hekReader();

    void read_hek();
        void read_metadata();
            void read_basic_metadata();
            void read_encoding_metadata();
        void read_data();

    void write_pgm();
        void write_metadata();
        void write_data();
};


#endif //PROJECT_HUFFMAN_IN_KHAS_HEKREADER_H
