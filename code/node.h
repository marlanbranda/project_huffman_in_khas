#ifndef PROJECT_HUFFMAN_IN_KHAS_NODE_H
#define PROJECT_HUFFMAN_IN_KHAS_NODE_H


class node {
public:
    node* left;
    node* right;
    char symbol;
    int freq;

    // constructor
    node();

    node* create_parent(node* left, node* right);

    bool is_root(node* node);

};


#endif //PROJECT_HUFFMAN_IN_KHAS_NODE_H
