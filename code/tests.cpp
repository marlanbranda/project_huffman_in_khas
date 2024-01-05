#include <iostream>
#include <fstream>
#include "tests.h"
#include "pgmReader.h"
#include "freqTable.h"
#include "treeNode.h"
#include "miscellaneous.h"

void test1(){
    // read the file
    std::cout << "emre" << std::endl;
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)
//    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\screenshot.png";

    pgmReader pgmObj = pgmReader(filename);

    std::cout << "width:    " << pgmObj.width << std::endl;
    std::cout << "height:   " << pgmObj.height << std::endl;
    std::cout << "max_gray: " << pgmObj.max_gray << std::endl;
    std::cout << "data:     " << pgmObj.data << std::endl;
    std::cout << "data_size:" << pgmObj.data_size << std::endl;

    char* bytestream = pgmObj.data_as_array();

    for(int i=0; i<pgmObj.data_size; i++){
        std::cout << bytestream[i];
    }

}

void test2(){
    char ch1 = 'º';
    char ch2 = 'Ñ'; // overflowing happens these are all two bytes in utf8
    char ch3 = 'ö';

    char _trial1 = '~'; // 126 as expected
    char _trial2 = ' ' + '_'; // 32+95=127 as expected
    char _trial3 = ' ' + '`'; // 32+96 should be 128 but it is -128
    unsigned char _trial4 = ' ' + '`';
    unsigned char _trial5 = (unsigned char) _trial3;

    std::cout << (int)ch1 << std::endl;
    std::cout << (int)ch2 << std::endl;
    std::cout << (int)ch3 << std::endl;
    std::cout << (int)_trial1 << std::endl;
    std::cout << (int)_trial2 << std::endl;
    std::cout << (int)_trial3 << std::endl;
    std::cout << (int)_trial4 << std::endl;
    std::cout << (int)_trial5 << std::endl;
    std::cout << (int)(unsigned char)ch1 << std::endl;
    std::cout << (int)(unsigned char)ch2 << std::endl;
    std::cout << (int)(unsigned char)ch3 << std::endl;
}

void test3(){
    // read the file
    std::cout << "emre" << std::endl;
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)
//    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\screenshot.png";

    pgmReader pgmObj = pgmReader(filename);

    std::cout << "width:    " << pgmObj.width << std::endl;
    std::cout << "height:   " << pgmObj.height << std::endl;
    std::cout << "max_gray: " << pgmObj.max_gray << std::endl;
    std::cout << "data:     " << pgmObj.data << std::endl;
    std::cout << "data_size:" << pgmObj.data_size << std::endl;

    char* bytestream = pgmObj.data_as_array();

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\data_stream.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    // try to pair each byte with a number between 0 255
    for(int i=0; i<pgmObj.data_size; i++){
        auto ch = (unsigned char)bytestream[i];
        int num = (int) ch;
        txt_file << num << "\n";
    }

}

void test4(){

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);


    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\freq_array.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    int** symbols_array = freqObj.freq_array;

    for(int i=0; i<256; i++) {
        for (int j=0; j<2; j++) {
            txt_file << symbols_array[i][j];
            txt_file << "\t";
        }
        txt_file << std::endl;
    }
}


void test5() {

    char ch1, ch2, ch3;
    unsigned char uch1, uch2, uch3;
    int in1, in2, in3;
    unsigned char uuch1, uuch2, uuch3;
    char tr1, tr2, tr3;

    ch1 = ' ' + '_'; // 32+95=127 as expected
    ch2 = ' ' + '`'; // 32+96 should be 128 but it is -128
    ch3 =  '<' + 'F'; // 60 + 70 it is probably -126

    uch1 = (unsigned char) ch1;
    uch2 = (unsigned char) ch2;
    uch3 = (unsigned char) ch3;

    in1 = (int) uch1;
    in2 = (int) uch2;
    in3 = (int) uch3;

    uuch1 = (unsigned char) in1;
    uuch2 = (unsigned char) in2;
    uuch3 = (unsigned char) in3;

    tr1 = (char) uuch1;
    tr2 = (char) uuch2;
    tr3 = (char) uuch3;

    if(ch1==tr1)
        std::cout << "ch1 and tr1 is same" << std::endl;

    if(ch2==tr2)
        std::cout << "ch2 and tr2 is same" << std::endl;

    if(ch2==tr2)
        std::cout << "ch3 and tr3 is same" << std::endl;

}

void test6(){
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_6.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out | std::ios::binary);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    txt_file << freqObj.unique_count << "\n";

    for(int i=0; i<freqObj.unique_count; i++){
        char ch = freqObj.unique_array[i];
        txt_file.write(&ch, sizeof(char));
        txt_file.write("\n", sizeof(char));
    }

}

void test7(){
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\bTree_leaf_nodes.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    if(binaryTreeObj.leaf_nodes != nullptr) {
        linkedNode* elem = binaryTreeObj.leaf_nodes;

        for(int i=0; ; i++) {
            txt_file << "elem " << i << " of linked node freq:      " << elem->dataNode->freq << std::endl;
            txt_file << "elem " << i << " of linked node symbol:    " << (int)(unsigned char)elem->dataNode->symbol << std::endl;
            if(elem->next != nullptr) {
                elem = elem->next;
            }
            else
                break;
        }

    }
}