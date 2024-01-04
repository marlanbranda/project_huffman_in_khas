#include "freqTable.h"

freqTable::freqTable(char *data_stream, int size) {
    this->unique_count = this->count_unique_symbols(data_stream);
    this->unique_array = this->create_unique_array(data_stream, size);
    this->unique_freq = this->create_frequency_array(data_stream,  size);
}

int freqTable::count_unique_symbols(char *data_stream) {

}

char *freqTable::create_unique_array(char *data_stream, int size) {
    return nullptr;
}

int *freqTable::create_frequency_array(char *data_stream, int size) {
    return nullptr;
};
