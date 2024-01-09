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
            throw std::logic_error("Usage: input_file.pgm output_file.hek");
        }
        else
        {
            char* input_file_pgm = argv[1];
            char* output_file_hek = argv[2];
            std::string output_file_hek_str = output_file_hek;

            pgmReader pgmObj = pgmReader(input_file_pgm);
            freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
            binaryTree binaryTreeObj = binaryTree(&freqObj);

            // TODO simplify this function
            hekWriter hekWriterObj = hekWriter(output_file_hek_str,
                                               (short int)pgmObj.width,
                                               (short int)pgmObj.height,
                                               (short int)binaryTreeObj.leaf_nodes->length(),
                                               binaryTreeObj.encoding_matrix,
                                               pgmObj.data_size,
                                               pgmObj.data_as_array() );

            std::cout << "Output file size in bytes: " << hekWriterObj.output_file_size << "\n";
            std::cout << "Compression rate achieved: %" <<
                ((pgmObj.data_size - hekWriterObj.output_file_size) * 100 )/ pgmObj.data_size;
        }
    }
    catch(std::exception &err)
    {
        std::cout << err.what() << "\n";
        return 1;
    }
}