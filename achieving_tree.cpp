// in this file I will create the prototype for tree and functions regarding it

#include <iostream>

typedef struct huffman_node{
    float freq; 
    huffman_node* right;
    huffman_node* left;
    char data;
}huff_node;
