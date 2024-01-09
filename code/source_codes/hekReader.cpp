#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

#include "../header_files/hekReader.h"


hekReader::hekReader() {
    this->max_gray = 255;

}

void hekReader::read_hek(const std::string& hek_file_name) {
    std::ifstream hek_file_read(hek_file_name, std::ios::binary);
    if(!hek_file_read.is_open()){
        throw std::runtime_error("pgm file can not be opened");
    }

    hek_file_read.seekg(0, std::ios::end);

    this->hek_file_size =  hek_file_read.tellg();

    hek_file_read.seekg(0);

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

    this->encoding_matrix = new encoding_struct[encoding_len];

    for(int i=0; i<encoding_len; i++)
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

    /*
     *
     * HERE WE READ DATA
     *
     */

    std::streampos curr = hek_file_read.tellg();
    hek_file_read.seekg(0, std::ios::end);
    std::streampos end = hek_file_read.tellg();

    hek_file_read.seekg(curr);

    int data_encoded_len = int(end) - int(curr);
    char* data_encoded = new char[data_encoded_len];

    hek_file_read.read(data_encoded, sizeof(char) * data_encoded_len); // NOLINT(*-narrowing-conversions)
    hek_file_read.close();


    std::string data_stream;
    std::string buffer;
    int pos=0;
    unsigned char mask = 0b10000000;
    // one char at a time
    for(int i=0; i < data_encoded_len; i++) {
        while(pos<8)
        {
            // mask
            if ((mask) & data_encoded[i]) {
                buffer += '1';
            } else {
                buffer += '0';
            }
            // RSH the mask
            pos++;
            mask >>= 1;

            // check the buffer
            for(int j=0; j< encoding_len; j++){
                if(encoding_matrix[j].binary_encoding == buffer)
                {
                    data_stream += encoding_matrix[j].symbol;
                    buffer.clear();
                    break;
                }
            }

        }
        pos = 0;
        mask = 0b10000000;

        if(buffer.length() >= 16){
            std::cerr << "this is buffer : " << buffer << std::endl;
            throw std::logic_error("buffer enlarged too much");
        }
    }

    this->data_stream = data_stream;
    this->data_size = this->data_stream.length(); // NOLINT(*-narrowing-conversions)
}


hekReader::~hekReader() {
    delete[] this->encoding_matrix;
    this->encoding_matrix = nullptr;
}

#pragma clang diagnostic pop