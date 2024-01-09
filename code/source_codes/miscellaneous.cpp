#include "../header_files/miscellaneous.h"
#include <stdexcept>

int ASCII_char_to_int(char ch){
    int number;

    if(ch >= '0' && ch <= '9'){
        number = (int)ch - '0';
    }
    else{
        throw std::range_error("char is not number");
    }

    return number;
}

int ASCII_str_to_int(std::string &str){
    int number = 0;
    int temp_num;
    int digit_count=1;

    for(int i= str.length()-1 ; i >= 0; i--){
        char ch = str[i];
        temp_num = ASCII_char_to_int(ch);
        number += temp_num * digit_count;
        digit_count *= 10;
    }

    return number;
}

linkedNode* create_dummy_linked_node(){
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
    return currLN;
};

void print_linked_node(linkedNode* currLN){
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
    std::cout << std::endl << "**********************************" << std::endl;

};


