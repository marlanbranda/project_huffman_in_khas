#include <iostream>
#include <bitset>
#include "tests.h"
#include "pgmReader.h"
#include "freqTable.h"
#include "miscellaneous.h"


int main(int argc, char *argv[])
{
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);


    test5();

}