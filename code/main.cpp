#include <iostream>
#include "pgmReader.h"
#include "miscellaneous.h"

int main(int argc, char *argv[])
{
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\pgm_files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

}