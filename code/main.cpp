#include <iostream>
#include <bitset>

#include "tests.h"

#include "pgmReader.h"
#include "freqTable.h"
#include "treeNode.h"
#include "hekWriter.h"
#include "hekReader.h"
#include "miscellaneous.h"


int main(int argc, char *argv[])
{
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);

    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    treeNode* root = binaryTreeObj.root;

    test9();

    /*
     * PSEUDO CODE
     *
     * unique_arr = freqTable.unique_array
     *
     *
     *
     *
     */

}