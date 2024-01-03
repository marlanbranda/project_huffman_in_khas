#include <iostream>
#include "pgmReader.h"
#include "miscellaneous.h"

int main(int argc, char *argv[])
{
    // read the file
    std::cout << "emre" << std::endl;
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\pgm_files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)
//    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\pgm_files\\screenshot.png";

    pgmReader pgmObj = pgmReader(filename);

    std::cout << "width:    " << pgmObj.width << std::endl;
    std::cout << "height:   " << pgmObj.height << std::endl;
    std::cout << "max_gray: " << pgmObj.max_gray << std::endl;
    std::cout << "data:     " << pgmObj.data << std::endl;
    std::cout << "data_size:" << pgmObj.data_size << std::endl;

}