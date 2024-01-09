#include "../header_files/hekWriter.h"


hekWriter::hekWriter(std::string &filename,
                     short int width,
                     short int height,
                     short int len_of_encoding,
                     encoding_struct* encoding_matrix,
                     int data_size,
                     char* data_stream) {

    std::ofstream file;
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("pgm file can not be opened");
    }

    // width,height
    char *wid_ch = (char *) &width;
    char *hei_ch = (char *) &height;
    file.write(wid_ch, sizeof(short int));
    file.write(hei_ch, sizeof(short int));

    // TODO this should be calculated
    this->padding_byte = 'E';
    file.write(&padding_byte, sizeof(char));

    //
    file.write((char *) &len_of_encoding, sizeof(short int));

    // one char for symbol, chars for encoding
    // (int i = 0; i < len_of_encoding; i++)
    // TODO change loop to for (int i = 0; i < len_of_encoding; i++)
    for (int i = 0; i < len_of_encoding; i++) {

        file.write(&encoding_matrix[i].symbol, sizeof(char));

        std::string bin_str = encoding_matrix[i].binary_encoding;

        char temp = (char) (unsigned char) bin_str.length();
        file.write(&temp, sizeof(char));

        // std::cout << bin_str << std::endl; // TODO REMOVE AFTER FINISHING

        short int pos = 0;
        char byte = 0b00000000;
        unsigned char mask = 0b10000000;
        for (int k = 0; k < bin_str.length(); k++) {
            if (bin_str[k] != '0') {
                byte = byte | mask;
            }

            mask >>= 1;
            pos++;
            if (pos == 8) {
                mask = 0b10000000;
                pos = 0;
                file.write(&byte, sizeof(char));
                byte = 0b00000000;
            }
        }
        if(pos!=0) {
            file.write(&byte, sizeof(char));
        }
    }


    // now the data
    // for each char in datastream
    std::string buffer;
    for(int i=0; i<data_size; i++){
        std::string bin_str;
        // find the encoding for this char
        for(int j=0; j<len_of_encoding; j++){
            if(encoding_matrix[j].symbol == data_stream[i]) {
                bin_str = encoding_matrix[j].binary_encoding;
                break;
            }
        }

        buffer.append(bin_str);
        while(buffer.length() >= 8) {
            short int pos = 0;
            char byte =          0b00000000;
            unsigned char mask = 0b10000000;
            for (int k = 0; k < 8; k++) {
                if (buffer[k] != '0') {
                    byte = byte | mask;
                }
                mask >>= 1;
                pos++;
            }
            file.write(&byte, sizeof(char));
            buffer.erase(0, 8);
        }
    }


    // padding will now has to be calculated
    // last things in the buffer will be written
    short int pos = 0;
    char byte = 0b00000000;
    unsigned char mask = 0b10000000;
    for (int k = 0; k < buffer.length(); k++) {
        if (buffer[k] != '0') {
            byte = byte | mask;
        }

        mask >>= 1;
        pos++;
        if (pos == 8) {
            mask = 0b10000000;
            pos = 0;
            file.write(&byte, sizeof(char));
            byte = 0b00000000;
        }
    }
    if(pos!=0) {
        file.write(&byte, sizeof(char));

        // padding value should be extracted with (int)(unsigned char)
        this->padding_byte = (char)(unsigned char)(8 - pos);
        file.seekp(4); // 5th byte is padding byte;
        file.write(&padding_byte, sizeof(char));
    }

    file.seekp(0, std::ios::end);
    this->output_file_size = file.tellp();

}