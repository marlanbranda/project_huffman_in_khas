#include "../header_files/tests.h"

/*
 * TEST 1: this test prints whether pgmReader correctly parses the metadata
 *         also prints all file char by char to check if there is problem in
 *         data_as_array() and data_size members of pgmReader
 */

void test1(){

    // read the file
    std::cout << "emre" << std::endl;
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
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

/*
 * TEST 2: I made some experiment on type casting between c types
 */

void test2(){
    char ch1 = 'º';
    char ch2 = 'Ñ'; // overflowing happens in all three bytes
    char ch3 = 'ö'; // because they are represented with two bytes by utf-8

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

/*
 * TEST 3: I turn te every char to value between [0-255], just to preparation for freqTable
 */
void test3(){

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);

    char* bytestream = pgmObj.data_as_array();

    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test3_data_stream.txt";
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

/*
 * TEST 4: let you see the freqTable, chars and their frequency in one line
 */
void test4(){

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);


    std::string txt_file_path = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test4_freq_array.txt";
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

/*
 * TEST 5: expansion to test3, I test if casting backwards also works
 */
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

/*
 * TEST 6: other members of freqTable
 */
void test6(){
    std::string filename =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm";
    pgmReader pgmObj = pgmReader(filename);
    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    std::string txt_file_path =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test6_freqTable.txt";
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

/*
 * TEST 7: leaf_node object of binaryTree if its parallel with freqTable
 */
void test7(){
    std::string filename =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);

    std::string txt_file_path =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test7_leaf_nodes.txt";
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

/*
 * TEST 9: this test will provide a visual way to see encodings of chars
 *         which will be created by encoding_matrix in binaryTree class
 */
void test9(){

    std::string filename =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);

    std::string txt_file_path =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test9_encoding_matrix.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    for(int i=0; i < 5 ; i++) {
        txt_file << binaryTreeObj.encoding_matrix[i].symbol << "\t" << binaryTreeObj.encoding_matrix[i].binary_encoding << std::endl;
    }
}


/*
 * TEST 10: here I create linkedNodeList manually to test
 *          and visually see if swap functions works properly
 */
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

    // PRINTING BEFORE MANIPULATION
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

    // PRINTING AFTER MANIPULATION
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

/*
 * TEST 11: prototype of sort_at_least_two
 *          starting linkedListNode with random value treeNodes
 *          then taking least amount into start of list
 */
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

/*
 * TEST 12: sorting the least two then creating parent node of them
 *          then removing the second element
 *          only for one time
 */
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


/*
 * TEST 13: sorting the least two then creating parent node of them
 *          then removing the second element
 *          recursively to build tree and find the root
 *          printing at every parenting stage to closely watch progress
 */
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

/*
 * TEST 14: sorting the least two then creating parent node of them
 *          then removing the second element
 *          recursively to build tree and find the root
 *          printing at every parenting stage to closely watch progress
 */
void test14(){
    std::string filename =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    char* bytestream = pgmObj.data_as_array();

    freqTable freqObj = freqTable(bytestream, pgmObj.data_size);

    binaryTree binaryTreeObj = binaryTree(&freqObj);
    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    treeNode* root = binaryTreeObj.root;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

    std::string txt_file_path =
            "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test14_bCodes_from_leaf_nodes.txt";
    std::fstream txt_file;
    txt_file.open(txt_file_path, std::ios::out);
    if(!txt_file.is_open()){
        std::cerr << "file is not open";
    }

    for(int i=0; i<leaf_nodes->length(); i++){
        encoding_struct* elem = encoding_matrix;

        txt_file << (int)(unsigned char)(elem->symbol) << "\t" << elem->binary_encoding << std::endl;

        encoding_matrix++;
    }

}

/*
 * TEST 15: experimentation with bitwise operations
 *          as it would be crucial to both encoding and decoding
 *          variable lenght compressed data
 */
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

};

/*
 * TEST 16: wrote some code to parse from .hek file,
 *          I am testing if I get same results inside and outside the class method
 *          Additionally I test if the loop parses in correct way encoding table
 */
void test16(){

    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);
    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

    std::string hek_file_name = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test16_first_hek.hek"; // NOLINT(*-raw-string-literal)
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

/*
 * TEST 17: comparing the data and encodings derived from reading pgm file and hek file
 *
 */
void test17(){
    std::string filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    pgmReader pgmObj = pgmReader(filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);
    linkedNode* leaf_nodes = binaryTreeObj.leaf_nodes;
    encoding_struct* encoding_matrix = binaryTreeObj.encoding_matrix;

    std::string hek_file_name = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test17_compressed_file.hek"; // NOLINT(*-raw-string-literal)
    hekWriter hekWriterObj = hekWriter(hek_file_name,
                                       (short int)pgmObj.width,
                                       (short int)pgmObj.height,
                                       (short int)leaf_nodes->length(),
                                       encoding_matrix,
                                       pgmObj.data_size,
                                       pgmObj.data_as_array() );

    std::ifstream hek_file_read(hek_file_name, std::ios::binary);

    hekReader hekReaderObj = hekReader();

    hekReaderObj.read_hek(hek_file_name);

    int Tcount = 0;
    int Fcount = 0;

    char* data_stream = pgmObj.data_as_array();
    for(int i=0; i<pgmObj.data_size; i++)
    {
//        std::cout << i + 1 << "\t";
//        std::cout << (int)(unsigned char)data_stream[i] << ' ';
//        std::cout << (int)(unsigned char)hekReaderObj.data_stream[i] << ' ';
//        std::cout << '\n';

        if(data_stream[i] == hekReaderObj.data_stream[i]){
            Tcount++;
        }else{
            Fcount++;
        }

    }
    std::cout << "\n\n comparing the data_streams of pgmReader and hekReader \n";
    std::cout << "False count : " << Fcount << "\t" << "True count: " << Tcount << "\n \n";


//    encoding data is truly transferred
    Tcount = 0;
    Fcount = 0;

    data_stream = pgmObj.data_as_array();
    for(int i=0; i<leaf_nodes->length(); i++)
    {
//        encoding_matrix[i].print_encoding_struct();
//        std::cout << '\t';
//        hekReaderObj.encoding_matrix[i].print_encoding_struct();

        if(encoding_matrix[i].symbol == hekReaderObj.encoding_matrix[i].symbol
            && encoding_matrix[i].binary_encoding == hekReaderObj.encoding_matrix[i].binary_encoding){
            Tcount++;
        }else{
            Fcount++;
        }

    }
    std::cout << "\n\n comparing the encoding tables of pgmReader and hekReader \n";
    std::cout << "False count : " << Fcount << "\t" << "True count: " << Tcount;

};

void test18(){
    std::string pgm_filename = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_image1.pgm"; // NOLINT(*-raw-string-literal)
    std::string hek_file_name = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test18_compressed_file.hek"; // NOLINT(*-raw-string-literal)
    std::string pgm_output = "C:\\Users\\emrek\\CLionProjects\\project_huffman_in_khas\\files\\test_outputs\\output_test18_decompressed.pgm"; // NOLINT(*-raw-string-literal)

    pgmReader pgmObj = pgmReader(pgm_filename);
    freqTable freqObj = freqTable(pgmObj.data_as_array(), pgmObj.data_size);
    binaryTree binaryTreeObj = binaryTree(&freqObj);

    // TODO simplify this function
    hekWriter hekWriterObj = hekWriter(hek_file_name,
                                       (short int)pgmObj.width,
                                       (short int)pgmObj.height,
                                       (short int)binaryTreeObj.leaf_nodes->length(),
                                       binaryTreeObj.encoding_matrix,
                                       pgmObj.data_size,
                                       pgmObj.data_as_array() );

    hekReader hekReaderObj = hekReader();

    hekReaderObj.read_hek(hek_file_name);

    pgmWriter pgmWriterObj = pgmWriter(&hekReaderObj, pgm_output);
}