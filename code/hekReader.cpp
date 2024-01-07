#include "hekReader.h"


hekReader::hekReader() {
    char magic_number[3] = "P5";
    this->magic_number = magic_number;
    this->max_gray = 255;
}

void hekReader::read_hek(std::string hek_file_name) {
    std::ifstream hek_file_read(hek_file_name, std::ios::binary);
    char temp;
    short int tempint;


    /*
     *
     * HERE WE READ ENCODING MATRIX AND METADATA
     *
     */

    // width
    hek_file_read.read((char*)&tempint, sizeof(short int));
    this->width = tempint;

    // height
    hek_file_read.read((char*)&tempint, sizeof(short int));
    this->height = tempint;

    // padding
    hek_file_read.read(&temp, sizeof(char));
    this->padding_byte = temp;

    //encoding len
    hek_file_read.read((char*)&tempint, sizeof(short int));
    this->encoding_len = tempint;

    this->encoding_matrix = new encoding_struct[encoding_len]; // TODO CHANGE THIS TO ENCODING LEN

    for(int i=0; i<encoding_len; i++) // TODO CHANGE THIS TO ENCODING LEN
    {
        // symbol
        hek_file_read.read(&temp, sizeof(char));
        encoding_matrix[i].symbol = temp;

        // len of binary encoding
        hek_file_read.read(&temp, sizeof(char));
        int len_of_bincoding = (int) (unsigned char) temp;


        for (int k=(int)(unsigned char)temp; k > 0;) {

            hek_file_read.read(&temp, sizeof(char));

            int pos = 0;
            char byte = temp;
            unsigned char mask = 0b10000000;
            for (int m = 0; m < len_of_bincoding; m++) {
                if (byte & mask) {
                    encoding_matrix[i].binary_encoding += '1';
                }else{
                    encoding_matrix[i].binary_encoding += '0';
                }
                pos++;

                if(pos==8){
                    hek_file_read.read(&temp, sizeof(char));
                    mask = 0b10000000;
                    pos=0;
                }

                mask >>= 1;
            }

            k -= 8;

        }
    }

    // read data

    // let's build tree first
    // leaf nodes
//    for(int i=0; i<encoding_len; i++){
//        // freq will not be important here as I will build tree based on the encoding matrix.binary_encoding
//        treeNode* treeNodeObj = new treeNode(0, encoding_matrix->symbol);
//
//    }

}

void hekReader::write_pgm(std::string pgm_file_name) {

}


