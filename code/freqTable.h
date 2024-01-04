#ifndef PROJECT_HUFFMAN_IN_KHAS_FREQTABLE_H
#define PROJECT_HUFFMAN_IN_KHAS_FREQTABLE_H


class freqTable {
public:
    int unique_count; // how many unique char is used in data_stream
    char* unique_array; // unique symbols
    int** unique_freq; // frequency of each symbol in same order with unique_array

    freqTable(char* data_stream, int size);
    ~freqTable();

    int** create_frequency_array(char* data_stream, int size);
    int count_unique_symbols() const;
    char* create_unique_array(char* data_stream);
};


#endif //PROJECT_HUFFMAN_IN_KHAS_FREQTABLE_H
