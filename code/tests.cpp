#include "tests.h"

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
    char _trial3 = ' ' + '`'; // 32+96 should be 128, but it is -128
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
    ch2 = ' ' + '`'; // 32+96 should be 128, but it is -128
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

void test8(){
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\replace_w_parent.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    if(binaryTreeObj.leaf_nodes != nullptr) {
        linkedNode* elem = binaryTreeObj.leaf_nodes;

        auto parentNode = binaryTreeObj.replace_with_parent(elem, elem->next);

        elem = parentNode;
        elem = elem->head();

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
    else
        std::cout << "leaf_nodes returned nullptr";
}

/*
 * THIS TEST IS DEFUNCT
 */
// this test will provide a visual way to see encodings of chars
// which will be created by encoding_matrix in binaryTree class
void test9(){

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-8-13.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\encoding_matrix.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out | std::ios::binary);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

//    for(int i=0; i < 5 ; i++) {
//
//        txt_file << binaryTreeObj.encoding_matrix[i][0] << binaryTreeObj.encoding_matrix[i][1] << std::endl;
//        std::cout << "dummy";
//    }
}

void test10(){

    linkedNode* currLN = new linkedNode;
    currLN->prev = nullptr;
    currLN->dataNode = new treeNode(5, 'g');
    for(int i=0; i<10; i++){
        linkedNode* nextLN = new linkedNode;
        currLN->next = nextLN;
        nextLN->prev = currLN;
        currLN = currLN->next;

        nextLN->dataNode = new treeNode(i*5, (char)(i+97) );
    }
    currLN = currLN->head();




    for(int i=0; ; i++) {
        std::cout << currLN << "(" << currLN->prev << ", " << currLN->dataNode->freq << ", " << currLN->next << ")" << std::endl;
        if(currLN->next != nullptr) {
            currLN = currLN->next;
        }
        else {
            break;
        }
    }

    linkedNode* emre = currLN->head();
    emre = emre->next->next;
    linkedNode* umut = currLN->tail();
    umut = umut->prev->prev;

    treeNode* nodeforeigner = new treeNode(931, '&');
    linkedNode* foreigner = new linkedNode();
    foreigner->next = nullptr;
    foreigner->prev = nullptr;
    foreigner->dataNode = nodeforeigner;

    emre->swap(foreigner);

    currLN = currLN->head();
    std::cout << std::endl << std::endl << std::endl;
    for(int i=0; ; i++) {
        std::cout << currLN << " (" << currLN->prev << ", " << currLN->dataNode->freq << ", " << currLN->next << ")" << std::endl;
        if(currLN->next != nullptr) {
            currLN = currLN->next;
        }
        else {
            break;
        }
    }
};

void test11(){

    linkedNode* currLN = new linkedNode;
    currLN->prev = nullptr;
    currLN->dataNode = new treeNode(5, 'g');
    for(int i=10; i>0; i--){
        linkedNode* nextLN = new linkedNode;
        currLN->next = nextLN;
        nextLN->prev = currLN;
        currLN = currLN->next;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist30(1,30); // distribution in range [1, 6]

        nextLN->dataNode = new treeNode(dist30(rng), (char)(i+97) );
    }
    currLN = currLN->head();




    for(int i=0; ; i++) {
        std::cout << currLN << "(" << currLN->prev << ", " << currLN->dataNode->freq << ", " << currLN->next << ")" << std::endl;
        if(currLN->next != nullptr) {
            currLN = currLN->next;
        }
        else {
            break;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    linkedNode* elem_head = currLN->head();
    for(int i=0; i<2; i++) {

        linkedNode* elem = elem_head->next;
        while (elem != nullptr) {
            if (elem_head->dataNode->freq >= elem->dataNode->freq) {
                elem->swap(elem_head);
            }
            if (elem->next != nullptr) {
                elem = elem->next;
            } else
                break;
        }
        elem_head = elem_head->next;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    currLN = currLN->head();
    std::cout << std::endl << std::endl << std::endl;
    for(int i=0; ; i++) {
        std::cout << currLN << " (" << currLN->prev << ", " << currLN->dataNode->freq << ", " << currLN->next << ")" << std::endl;
        if(currLN->next != nullptr) {
            currLN = currLN->next;
        }
        else {
            break;
        }
    }
};


void test12(){

    linkedNode* currLN = new linkedNode;
    currLN->prev = nullptr;
    currLN->dataNode = new treeNode(5, 'g');
    for(int i=10; i>0; i--){
        linkedNode* nextLN = new linkedNode;
        currLN->next = nextLN;
        nextLN->prev = currLN;
        currLN = currLN->next;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist30(1,30); // distribution in range [1, 6]

        nextLN->dataNode = new treeNode(dist30(rng), (char)(i+97) );
    }
    currLN = currLN->head();




    for(int i=0; ; i++) {
        std::cout << currLN << "(" << currLN->prev << ", " << currLN->dataNode << ", " << currLN->next << ")" << std::endl;
        if(currLN->next != nullptr) {
            currLN = currLN->next;
        }
        else {
            break;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    currLN = currLN->head();
    treeNode* root;

    while(currLN->next != nullptr) {
        currLN->sort_least_two();

        linkedNode *smallest_elem = currLN;
        linkedNode *smallest_second_elem = currLN->next;

        treeNode *parentTreeNode = new treeNode(smallest_elem->dataNode, smallest_second_elem->dataNode);
        smallest_elem->dataNode = parentTreeNode;
        smallest_second_elem->remove();
        root = parentTreeNode;
    }

    std::cout << root << root->freq << "\tleft:"<< root->left << "\t right:" << root->right;
    std::cout << root->left << root->freq << "\tleft:"<< root->left << "\t right:" << root->right;


    ///////////////////////////////////////////////////////////////////////////////////////////
    currLN = currLN->head();
    std::cout << std::endl << std::endl << std::endl;
    for(int i=0; ; i++) {
        std::cout << currLN << " (" << currLN->prev << ", " << currLN->dataNode->freq << ", " << currLN->next << ")" << std::endl;
        if(currLN->next != nullptr) {
            currLN = currLN->next;
        }
        else {
            break;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

};

void test13(){

    linkedNode* currLN = create_dummy_linked_node();
    print_linked_node(currLN);

    currLN = currLN->head();
    treeNode* root;

    while(currLN->next != nullptr) {
        currLN->sort_least_two();

        linkedNode *smallest_elem = currLN;
        linkedNode *smallest_second_elem = currLN->next;

        treeNode *parentTreeNode = new treeNode(smallest_elem->dataNode, smallest_second_elem->dataNode);
        smallest_elem->dataNode = parentTreeNode;
        smallest_second_elem->remove();
        root = parentTreeNode;

        print_linked_node(currLN);
    }

    std::cout << root  << "\tleft:"<< root->left << "\t right:" << root->right << std::endl;
    std::cout << root->left  << "\tleft:"<< root->left->left << "\t right:" << root->left->right << std::endl;
    std::cout << root->right  << "\tleft:"<< root->right->left << "\t right:" << root->right->right << std::endl;

};

void test14(){
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-9-15.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);

    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    treeNode* root = binaryTreeObj.root;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\encoding_matrix.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out | std::ios::binary);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    for(int i=0; i<leaf_nodes->length(); i++){
        encoding_struct* elem = encoding_matrix;

        txt_file << (int)(unsigned char)(elem->symbol) << "\t" << elem->binary_encoding << std::endl;

        encoding_matrix++;
    }

}

void test15(){

    std::string str;
    char byte = 0b01010101;
    unsigned char mask = 0b10000000;
    for (int k = 0; k < 8; k++) {
        if (byte & mask) {
            str += '1';
        }else{
            str += '0';
        }

        mask >>= 1;
    }

    std::cout << str;

    std::cout << std::endl << std::endl << std::endl;

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-78-36.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);
    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

//    std::cout << pgmObj.width << std::endl;
//    std::cout << pgmObj.height << std::endl;

    std::string hek_file_name = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test15.hek"; // NOLINT(*-raw-string-literal)
    hekWriter hekWriterObj = hekWriter(hek_file_name,
                                       (short int)pgmObj.width,
                                       (short int)pgmObj.height,
                                       (short int)leaf_nodes->length(),
                                       encoding_matrix,
                                       pgmObj.data_size,
                                       pgmObj.data_as_array() );

    // hek writer cout firts two binary encoding
    std::ifstream hek_file_read(hek_file_name, std::ios::binary);
    char temp;
    short int tempint;

    // width
    hek_file_read.read((char*)&tempint, sizeof(short int));
    std::cout << tempint << std::endl;

    // height
    hek_file_read.read((char*)&tempint, sizeof(short int));
    std::cout << tempint << std::endl;

    // padding
    hek_file_read.read(&temp, sizeof(char));
    std::cout << temp << std::endl;

    //encoding len
    hek_file_read.read((char*)&tempint, sizeof(short int));
    std::cout << "encoding len ;"<<tempint << std::endl;

    for(int i=0; i<10; i++)
    {    // symbol
        hek_file_read.read(&temp, sizeof(char));
        std::cout << (int) (unsigned char) temp << " symbol" << std::endl;

        // len of binary encoding
        hek_file_read.read(&temp, sizeof(char));
        std::cout << (int) (unsigned char) temp << " len of bincoding " << std::endl;

        for (int k=(int)(unsigned char)temp; k > 0;) {
            hek_file_read.read(&temp, sizeof(char));
            std::cout << (int) (unsigned char) temp << std::endl;
            k -= 8;
        }
    }



};

void test16(){

    std::string str;
    char byte = 0b01010101;
    unsigned char mask = 0b10000000;
    for (int k = 0; k < 8; k++) {
        if (byte & mask) {
            str += '1';
        }else{
            str += '0';
        }

        mask >>= 1;
    }

    std::cout << str;

    std::cout << std::endl << std::endl << std::endl;

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-78-36.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);
    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

    std::string hek_file_name = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test15.hek"; // NOLINT(*-raw-string-literal)
    hekWriter hekWriterObj = hekWriter(hek_file_name,
                                       (short int)pgmObj.width,
                                       (short int)pgmObj.height,
                                       (short int)leaf_nodes->length(),
                                       encoding_matrix,
                                       pgmObj.data_size,
                                       pgmObj.data_as_array() );

    // hek writer cout firts two binary encoding
    std::ifstream hek_file_read(hek_file_name, std::ios::binary);

    hekReader hekReaderObj = hekReader();

    hekReaderObj.read_hek(hek_file_name);

    std::cout << "\n\n\n\n";

    char temp;
    short int tempint;

    // width
    hek_file_read.read((char*)&tempint, sizeof(short int));
    std::cout << tempint << std::endl;

    // height
    hek_file_read.read((char*)&tempint, sizeof(short int));
    std::cout << tempint << std::endl;

    // padding
    hek_file_read.read(&temp, sizeof(char));
    std::cout << temp << std::endl;

    //encoding len
    hek_file_read.read((char*)&tempint, sizeof(short int));
    std::cout << "encoding len ;"<<tempint << std::endl;

    for(int i=0; i<20; i++)
    {    // symbol
        hek_file_read.read(&temp, sizeof(char));
        std::cout << (int) (unsigned char) temp << " symbol" << std::endl;

        // len of binary encoding
        hek_file_read.read(&temp, sizeof(char));
        std::cout << (int) (unsigned char) temp << " len of bincoding " << std::endl;

        for (int k=(int)(unsigned char)temp; k > 0;) {
            hek_file_read.read(&temp, sizeof(char));
            std::cout << (int) (unsigned char) temp << std::endl;
            k -= 8;
        }
    }

    std::cout << "\n\n\n\n";

    std::cout << hekReaderObj.width << '\n';
    std::cout << hekReaderObj.height << '\n';
    std::cout << hekReaderObj.padding_byte << '\n';
    std::cout << hekReaderObj.encoding_len << '\n';

};


void test17(){
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\aug-78-36.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);
    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

    // encoding table we derive from the pgm file
//    for(int i=0; i<leaf_nodes->length();i++) {
//        encoding_matrix[i].print_encoding_struct();
//    }

    std::string hek_file_name = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test15.hek"; // NOLINT(*-raw-string-literal)
    hekWriter hekWriterObj = hekWriter(hek_file_name,
                                       (short int)pgmObj.width,
                                       (short int)pgmObj.height,
                                       (short int)leaf_nodes->length(),
                                       encoding_matrix,
                                       pgmObj.data_size,
                                       pgmObj.data_as_array() );


//     hek writer COUT firts two binary encoding


    std::ifstream hek_file_read(hek_file_name, std::ios::binary);

    hekReader hekReaderObj = hekReader();

    // COUT!! hek reader couts firts ten elements of binary encoding
    hekReaderObj.read_hek(hek_file_name);
//
//    std::cout << "\n\n\n\n\n\n\n\n";
//
    // pgm file data stream



    char* data_stream = pgmObj.data_as_array();
    for(int i=0; i<20; i++)
    {
        std::cout << (int)(unsigned char)data_stream[i] << ' ';
    }

    std::cout << '\n';

    for(int i=0; i<20; i++)
    {
        std::cout << (int)(unsigned char)hekReaderObj.data_stream[i] << ' ';
    }


    // hek_reader decoded char stream


};