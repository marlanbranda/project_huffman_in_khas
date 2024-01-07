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


        int pos = 0;
        for (int k=(int)(unsigned char)temp; k > 0;) {

            hek_file_read.read(&temp, sizeof(char));

            char byte = temp;
            unsigned char mask = 0b10000000;
            while ( pos < len_of_bincoding) {
                if (byte & mask) {
                    encoding_matrix[i].binary_encoding += '1';
                }else{
                    encoding_matrix[i].binary_encoding += '0';
                }
                pos++;
                mask >>= 1;

                // if encoding contains coding bigger than 15bits program will crash
                if(pos==8){
                    break;
                }

            }

            k -= 8;

        }
    }

//    for(int i=0; i<encoding_len; i++)
//    {
//        encoding_matrix[i].print_encoding_struct();
//    }

    /*
     *
     * HERE WE READ DATA
     *
     */

    std::streampos curr = hek_file_read.tellg();

    hek_file_read.seekg(0, std::ios::end);
    std::streampos end = hek_file_read.tellg();

    hek_file_read.seekg(curr);

    int data_stream_len = int(end) - int(curr);


    std::string data_stream;
    char* data_encoded = new char[data_stream_len];
    char* p_data_encoded = data_encoded;
    int p_data_encoded_index = 0;
    hek_file_read.read(data_encoded, sizeof(char) * data_stream_len);
    hek_file_read.close();

    //
//    for(int i=0; i<1; i++) {
//        std::cout << (int)(unsigned int)data_encoded[0] << std::endl;
//    }


    std::string buffer;
    int pos=0;
    unsigned char mask = 0b10000000;

    // one char at a time
    for(int i=0; i<encoding_len; i++){

        do {
            // encoded datadan bir bit ekle
            if ((mask) & (*p_data_encoded)) {
                buffer += '1';
            } else {
                buffer += '0';
            }
            pos++;
            mask >>= 1;
            if (pos == 8) {
                pos = 0;
                mask = 0b10000000;
                if(p_data_encoded_index != data_stream_len - 1 ) {
                    p_data_encoded += 1;
                    p_data_encoded_index += 1;
                }
            }

            // check the buffer
            for(int j=0; j< encoding_len; j++){
                if(encoding_matrix[j].binary_encoding == buffer)
                {
                    data_stream += encoding_matrix[j].symbol;
                    buffer.clear();
                    break;
                }
            }
            if(buffer.length() >= 16){
                std::cerr << "this is buffer : " << buffer << std::endl;
                throw std::logic_error("buffer enlarged too much");
            }

        }while(!buffer.empty());
    }
    this->data_stream = data_stream;


}

void hekReader::write_pgm(std::string pgm_file_name) {

}


