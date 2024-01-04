#include "freqTable.h"

#include <iostream>
#include <fstream>

freqTable::freqTable(char *data_stream, int size) {
    this->unique_freq = create_frequency_array(data_stream, size);
    this->unique_count = count_unique_symbols();
    this->unique_array = create_unique_array();
}

int** freqTable::create_frequency_array(char *data_stream, int size) {

    int** symbols_array = new int*[256];
    for(int i=0; i<256; i++){
        symbols_array[i] = new int[2];
        symbols_array[i][0] = i; // 0 index for symbol, 1 index is freq
        symbols_array[i][1] = 0;
    }

    for(int i=0; i<size; i++){
        auto ch = (unsigned char) data_stream[i];
        int num = (int) ch;
        symbols_array[num][1] += 1;
    }

    return symbols_array;
};

int freqTable::count_unique_symbols() const {
    int num = 0;
    int** symbols_array = this->unique_freq;

    for(int i=0; i<256; i++){
        if( symbols_array[i][1] >= 1)
            num++;
    }

    return num;
}

char* freqTable::create_unique_array() {
    char* unique_chars = new char[this->unique_count];
    int** symbols_array = this->unique_freq;
    int num = 0;

    for(int i=0; i<256; i++){
        if( symbols_array[i][1] >= 1) {
            unique_chars[num] = (char)(unsigned char)symbols_array[i][0];
            num++;
        }
    }

    return unique_chars;
}

freqTable::~freqTable() = default;


