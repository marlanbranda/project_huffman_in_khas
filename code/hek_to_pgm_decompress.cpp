#include <iostream>

#include "header_files/tests.h"

#include "header_files/pgmReader.h"
#include "header_files/freqTable.h"
#include "header_files/treeNode.h"
#include "header_files/hekWriter.h"
#include "header_files/hekReader.h"
#include "header_files/pgmWriter.h"
#include "header_files/miscellaneous.h"


int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3) {
            throw std::logic_error("Usage: input_file.hek output_file.pgm");
        }
        else
        {
            char* input_file_hek = argv[1];
            char* output_file_pgm = argv[2];

            hekReader hekReaderObj = hekReader();

            hekReaderObj.read_hek(input_file_hek);

            pgmWriter pgmWriterObj = pgmWriter(&hekReaderObj, output_file_pgm);

            std::cout << "Input file size in bytes: " << hekReaderObj.hek_file_size <<"\n";
            std::cout << "Output file size in bytes: " << hekReaderObj.data_size + 14;
        }
    }
    catch(std::exception &err)
    {
        std::cout << err.what() << "\n";
        return 1;
    }
}