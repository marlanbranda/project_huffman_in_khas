#include <iostream>


typedef struct huffman_node
{
    void* right;
    void* left;
};


int main()
{

    // node working with two char
    struct huffman_node node1;
    // node working with two char
    struct huffman_node node2;
    // node working with two huffman_node
    struct huffman_node node3;
    // node working with one huffman_node, one char
    struct huffman_node node4;

    char a = 'a';
    char b = 'b';
    
    char x = 'x';
    char y = 'y';

    node1.right = &a;
    node1.left = &b;

    node2.right = &x;
    node2.left = &y;

    node3.right = &node1;
    node3.left = &b;

    node4.right = &node1;
    node4.left = &node2;

    // std::cout << *(char*)node1.right << std::endl;

    // std::cout << *(char*)node3.left << std::endl;
    
    try
    {
        // std::cout << *(char*)(*(huffman_node*)node3.right).right << std::endl;
        huffman_node dummy_obj = *(char*)node3.right;
    }
    catch(...)
    {
        std::cout << "gotcha";
    }

    return 0;

}
