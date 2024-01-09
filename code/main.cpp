#include <iostream>
#include <bitset>

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
            throw std::logic_error("Usage1: compress input_file.pgm output_file.hek \n"
                                   "Usage2: decompress input_file.hek output_file.pgm");
        }
        else
        {

        }
    }
    catch(std::exception &err)
    {
        std::cerr << err.what() << "\n";
        return 1;
    }



}