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

    while (curr->next != nullptr) {
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

binaryTree::binaryTree(freqTable* freqObj) {
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
    prev_leaf->next = nullptr;

    linkedNode* head_of_node = prev_leaf->head();

    return head_of_node;
}

treeNode* binaryTree::create_tree(linkedNode linkedNodeObj) {
    linkedNode* elem = &linkedNodeObj;

    while(true){
        elem = elem->head();

        if(elem->length() == 1){
            return elem->dataNode;
        }

        else if(elem->length() == 2){
            linkedNode* smallest_elem = elem;
            linkedNode* second_smallest_elem = elem->next;

            if ((smallest_elem->dataNode->freq) > (second_smallest_elem->dataNode->freq)) {
                linkedNode* temp = second_smallest_elem;
                second_smallest_elem = smallest_elem;
                smallest_elem = temp;
            }

            linkedNode *parentLinkedNode = replace_with_parent(smallest_elem, second_smallest_elem);
            return parentLinkedNode->dataNode;
        }

        else if(elem->length() >= 3){
            linkedNode* smallest_elem = elem;
            linkedNode* second_smallest_elem = elem->next;

            elem = elem->next;
            do{
                elem = elem->next;
                if ((smallest_elem->dataNode->freq) > (elem->dataNode->freq)) {
                    second_smallest_elem = smallest_elem;
                    smallest_elem = elem;
                }

            }while(elem->next != nullptr);

            __attribute__((unused))
            linkedNode* parentLinkedNode = replace_with_parent(smallest_elem, second_smallest_elem);

            elem = parentLinkedNode->head();
        }
    }

}

linkedNode* binaryTree::replace_with_parent(linkedNode* leftNode, linkedNode* rightNode) {
    linkedNode* parentLinkedNode = new linkedNode;
    treeNode* pointer_to_treeNode = new treeNode(leftNode->dataNode, rightNode->dataNode);

    parentLinkedNode->dataNode = pointer_to_treeNode;

    // remove from linkedNode
    if(rightNode->prev != nullptr){
        rightNode->prev->next = rightNode->next;
    }

    if(rightNode->next != nullptr){
        rightNode->next->prev = rightNode->prev;
    }

    // leftnode switch
    if(leftNode->prev != nullptr){
        parentLinkedNode->prev = leftNode->prev;
        leftNode->prev->next = parentLinkedNode;
    }
    else{
        parentLinkedNode->prev = nullptr;
    }

    if(leftNode->next != nullptr){
        parentLinkedNode->next = leftNode->next;
        leftNode->next->prev = parentLinkedNode;
    }
    else{
        parentLinkedNode->next = nullptr;
    }

//    delete leftNode;
//    delete rightNode;

    return parentLinkedNode;
}

char** binaryTree::create_encoding_matrix() {
    // traverse the tree and get the encodings

        // get the lenght of leaf_nodes

        // dynamic memory allocation in appropriate size

        // walk on leaf_nodes
            // go to parent, add 0 if left child, add 1 if right child to string
            // for each create an encoding <char>10101001

    return nullptr;
}

