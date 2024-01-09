#include "../header_files/pgmWriter.h"

pgmWriter::pgmWriter(hekReader* hekReaderObj, std::string filename) {
    this->max_gray = 255;
    this->width = hekReaderObj->width;
    this->height = hekReaderObj->height;
    this->filename = filename; // NOLINT

    std::ofstream file;
    file.open(filename, std::ios::binary);
    if(!file.is_open()){
        throw std::runtime_error("pgm file can not be opened");
    }

    file << "P5\n" << this->width << ' ' << this->height << '\n'  << this->max_gray << '\n';

    for(int i=0; i<hekReaderObj->data_size; i++)
    {
        char temp_char = hekReaderObj->data_stream[i];
        file.write(&temp_char, sizeof(char));
    }

    this->pgm_file_size = file.tellp();
}
