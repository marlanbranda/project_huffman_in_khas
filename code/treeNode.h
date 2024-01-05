#ifndef PROJECT_HUFFMAN_IN_KHAS_TREENODE_H
#define PROJECT_HUFFMAN_IN_KHAS_TREENODE_H

#include <climits>
#include <iostream>

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

    treeNode* dataNode;
    linkedNode* prev;
    linkedNode* next;

    int length();
    linkedNode* head();
    linkedNode* tail();

};


class binaryTree {
public:
    linkedNode* leaf_nodes;
    treeNode* root;

    explicit binaryTree(freqTable* freqObj); // NOLINT(*-explicit-constructor)

    linkedNode* create_linked_node(freqTable* freqObj); // every element is leaf-node in returning
    treeNode* create_tree(linkedNode linkedNodeObj); // returning the root
    linkedNode* replace_with_parent(linkedNode* leftNode, linkedNode* rightNode);

};

#endif //PROJECT_HUFFMAN_IN_KHAS_TREENODE_H
