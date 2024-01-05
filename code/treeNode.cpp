#include "treeNode.h"

treeNode::treeNode(int freq, char symbol) {
    this->freq = freq;
    this->symbol = symbol;

    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

treeNode::treeNode(treeNode* leftNode, treeNode* rightNode) {
    this->left = leftNode;
    this->right = rightNode;

    this->freq = leftNode->freq + rightNode->freq;

    this->parent = nullptr;
    leftNode->parent = this;
    rightNode->parent = this;

    // symbols of the nodes that left and right is not nullptr is not important
    this->symbol = leftNode->symbol;
}

int linkedNode::length() {
    linkedNode* curr = this->head();

    int count = 1;

    for ( ;curr->next != nullptr; ) {
        curr = curr->next;
        count++;
    }
    return count;
}

linkedNode* linkedNode::head() {
    linkedNode* curr = this;

    for(int i=0;;i++) {
        if (curr->prev != nullptr)
            curr = curr->prev;
        else
            break;
    }
    return curr;
}

linkedNode* linkedNode::tail() {
    linkedNode* curr = this;

    for(int i=0;;i++) {
        if (curr->next != nullptr)
            curr = curr->next;
        else
            break;
    }
    return curr;
}

binaryTree::binaryTree(freqTable *freqObj) {
    this->leaf_nodes = create_linked_node(freqObj);
    this->root = create_tree(*(this->leaf_nodes));

}

linkedNode* binaryTree::create_linked_node(freqTable* freqObj) {

    linkedNode* prev_leaf = nullptr;

    for(int i=0; i<freqObj->unique_count; i++){

        char symbol = freqObj->unique_array[i];
        int symbol_int_repr = (int)(unsigned char)symbol;
        int freq = freqObj->freq_array[symbol_int_repr][1];
        treeNode* dataNode = new treeNode(freq, symbol);

        linkedNode* curr_leaf = new linkedNode;

        curr_leaf->dataNode = dataNode;

        curr_leaf->prev = prev_leaf;
        if(prev_leaf != nullptr)
            prev_leaf->next = curr_leaf;
        prev_leaf = curr_leaf;
    }

    linkedNode* head_of_node = prev_leaf->head();

    return head_of_node;
}

treeNode* binaryTree::create_tree(linkedNode linkedNodeObj) {
    //

    return nullptr;
}

linkedNode*  binaryTree::replace_with_parent(linkedNode* leftNode, linkedNode* rightNode) {
    linkedNode* parentNode = new linkedNode;
    parentNode->dataNode = create_parent_node(leftNode->dataNode, rightNode->dataNode);

    // right kicked out of list
    rightNode->next->prev = rightNode->prev;
    rightNode->prev->next = rightNode->next;
    delete rightNode;

    // parent takes the place of left
    parentNode->prev = leftNode->prev;
    parentNode->next = leftNode->next;
    delete leftNode;


    return parentNode;
}

treeNode* binaryTree::create_parent_node(treeNode* leftNode, treeNode* rightNode) {
    auto parentNode = new treeNode(leftNode, rightNode);
    return parentNode;
}

