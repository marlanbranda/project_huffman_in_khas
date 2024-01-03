#include "miscellaneous.h"
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