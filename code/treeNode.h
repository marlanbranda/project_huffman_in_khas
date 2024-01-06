#ifndef PROJECT_HUFFMAN_IN_KHAS_TREENODE_H
#define PROJECT_HUFFMAN_IN_KHAS_TREENODE_H

#include <climits>
#include <iostream>
#include <string>

#include "freqTable.h"


struct treeNode {
public:
    treeNode* left;
    treeNode* right;
    treeNode* parent;
    char symbol;
    int freq;

    treeNode(int freq, char symbol);
    treeNode(treeNode* leftNode, treeNode* rightNode);

};

struct linkedNode {
public:

    treeNode* dataNode;
    linkedNode* prev;
    linkedNode* next;

    int length();
    linkedNode* head();
    linkedNode* tail();
    void remove();
    void swap(linkedNode* param);

};


class binaryTree {
public:
    linkedNode* leaf_nodes;
    treeNode* root;
    char** encoding_matrix; // TODO add the construction of this to constructor at the end

    explicit binaryTree(freqTable* freqObj); // NOLINT(*-explicit-constructor)
    ~binaryTree();

    linkedNode* create_linked_node(freqTable* freqObj); // every element is leaf-node in returning
    linkedNode* deep_copy_linked_list(linkedNode* linkedNodeObj);
    treeNode* create_tree(linkedNode* linkedNodeObj); // TODO tree is not looking optimal & work on it
    linkedNode* replace_with_parent(linkedNode* leftLinkedNode, linkedNode* rightLinkedNode);
    char** create_encoding_matrix(); // TODO now in pseudocode stage
};

#endif //PROJECT_HUFFMAN_IN_KHAS_TREENODE_H
