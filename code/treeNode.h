#ifndef PROJECT_HUFFMAN_IN_KHAS_TREENODE_H
#define PROJECT_HUFFMAN_IN_KHAS_TREENODE_H

#include "freqTable.h"


typedef struct treeNode {
public:
    treeNode* left;
    treeNode* right;
    char symbol;
    int freq;

    treeNode(int freq, char symbol);
    treeNode(treeNode* leftNode, treeNode* rightNode);

}treeNode;


struct linkedNode {

    treeNode* treeNode;
    linkedNode* prev;
    linkedNode* next;

    int length();
    linkedNode* head();
    linkedNode* tail();
};


class binaryTree {
public:
    linkedNode* leafNodes;

    linkedNode* create_linked_node(freqTable* freqObj); // every element is leaf-node in returning

    treeNode* create_tree(linkedNode linkedNodeObj); // returning the root

    treeNode* create_parent_node(treeNode* leftNode, treeNode* rightNode);
    void replace_with_parent(treeNode* leftNode, treeNode* rightNode, treeNode* parentNode);

    explicit binaryTree(freqTable* freqObj);
};

#endif //PROJECT_HUFFMAN_IN_KHAS_TREENODE_H
