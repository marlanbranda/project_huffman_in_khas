#include "../header_files/pgmReader.h"
#include "../header_files/miscellaneous.h"

pgmReader::pgmReader(const std::string& filename) { // NOLINT(*-pro-type-member-init)

    this->filename = filename;
    std::ifstream file;
    file.open(filename, std::ifstream::in | std::ifstream::binary);

    if(!file.is_open()){
        throw std::runtime_error("pgm file can not be opened");
    }

    // for checking the P5
    char read_number[3];
    const char* magic_number = "P5";
    file.get(read_number, 3);
    if( std::strcmp(read_number, magic_number) != 0 ){
        throw std::runtime_error("P5 is not found");
    }

    // parse width, height and maxgray
    std::string str[3];
    file.seekg(3);

    // this part gets every line into string array in metadata
    int k = 0;
    for(int i=0; i<50; i++){
        char ch;
        file.get(ch);
        if( std::isspace(ch) ){
            k++;
            if(k > 2)
                break;
        }
        else
            str[k] += ch;
    }
    this->data = file.tellg();
    this->width = ASCII_str_to_int(str[0]);
    this->height = ASCII_str_to_int(str[1]);
    this->max_gray = ASCII_str_to_int(str[2]);

    if(this->max_gray != 255){
        throw std::range_error("max_range is not 255");
    }

    file.seekg(0, std::ios::end);
    std::streampos end = file.tellg();

    // file size minus metadata
    this->data_size = (int)(end - data);
    this->data_stream = new char[this->data_size];

    file.close();
}

char* pgmReader::data_as_array() const {

    std::ifstream file;
    file.open(this->filename, std::ifstream::in | std::ifstream::binary);
    file.seekg(this->data);
    file.read(data_stream, data_size);
    file.close();

    return this->data_stream;
}

pgmReader::~pgmReader(){
    delete[] this->data_stream;
    data_stream = nullptr;
};
