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

void linkedNode::remove() {

    if(this->prev != nullptr){
        this->prev->next = this->next;
    }

    if(this->next != nullptr){
        this->next->prev = this->prev;
    }

    delete this;
}

// 0x58(null, EMR, 0x77)  0x77(0x58, UMT, 0x42) 0x42(0x77, ALI, 0x35) 0x35(0x42, VEL, 0x31) 0x31(0x35, AYS, 0x81) 0x81(0x31, HEL, null)
// 0x58(null, EMR, 0x77)  0x77(0x58, UMT, 0x42) 0x42(0x77, ALI, 0x35) 0x35(0x42, VEL, 0x31) 0x31(0x35, AYS, 0x81) 0x81(0x31, HEL, null)
//                        0x31(0x35, AYS, 0x81)                                             0x77(0x58, UMT, 0x42)

// 0x58(null, EMR, 0x77)  0x77(0x58, AYS, 0x42) 0x42(0x77, ALI, 0x35) 0x35(0x42, VEL, 0x31) 0x31(0x35, UMT, 0x81) 0x81(0x31, HEL, null)

// 0x77(0x58, UMT, 0x42)
// 0x31(0x35, AYS, 0x81)

void linkedNode::swap(linkedNode* param) {
    treeNode* temp = param->dataNode;
    param->dataNode = this->dataNode;
    this->dataNode = temp;
}

void linkedNode::sort_least_two() {
    linkedNode* elem_head = this->head();
    for(int i=0; i<2; i++) {

        linkedNode* elem = elem_head->next;
        while (elem != nullptr) {
            if (elem_head->dataNode->freq >= elem->dataNode->freq) {
                elem->swap(elem_head);
            }
            if (elem->next != nullptr) {
                elem = elem->next;
            } else
                break;
        }
        elem_head = elem_head->next;
    }
}


binaryTree::binaryTree(freqTable* freqObj) {
    this->leaf_nodes = create_linked_node(freqObj);
    this->root = create_tree((this->leaf_nodes));
//    this->encoding_matrix = create_encoding_matrix();
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

treeNode* binaryTree::create_tree(linkedNode* linkedNodeObj) {
    linkedNode* elem_original = linkedNodeObj;

    linkedNode* elem = deep_copy_linked_list(elem_original);

    treeNode* root;

    while(elem->next != nullptr) {
        elem->sort_least_two();

        linkedNode *smallest_elem = elem;
        linkedNode *smallest_second_elem = elem->next;

        treeNode *parentTreeNode = new treeNode(smallest_elem->dataNode, smallest_second_elem->dataNode);
        smallest_elem->dataNode = parentTreeNode;
        smallest_second_elem->remove();
        root = parentTreeNode;
    }
    return root;
}

linkedNode* binaryTree::replace_with_parent(linkedNode* leftLinkedNode, linkedNode* rightLinkedNode) {
    linkedNode* parentLinkedNode = new linkedNode;
    treeNode* parentTreeNode = new treeNode(leftLinkedNode->dataNode, rightLinkedNode->dataNode);
    parentLinkedNode->dataNode = parentTreeNode;



    return parentLinkedNode;
}

char** binaryTree::create_encoding_matrix() {
    // traverse the tree and get the encodings
    linkedNode* elem = this->leaf_nodes;

    // get the lenght of leaf_nodes
    int len_of_leaves = elem->length();

    // dynamic memory allocation in appropriate size
    char** encoding_matrix = new char*[len_of_leaves];

    // walk on leaf_nodes
    for(int i=0; i < len_of_leaves; i++){
        std::string encoding;

        // go to parent, add 0 if left child, add 1 if right child to string
        treeNode* curr_node = elem->dataNode;
        encoding += curr_node->symbol;

        while(curr_node != this->root){
            treeNode* parent_node = curr_node->parent;
            if(parent_node->left == curr_node){
                encoding += "0";
            }
            else if(parent_node->right == curr_node){
                encoding += "1";
            }
            else{
                throw std::logic_error("parent and child has some problems");
            }
            curr_node = parent_node;
        }

        char* row = encoding_matrix[i];
        row = new char[encoding.length()];

        for(int j =0; j < encoding.length(); j++ ){
            row[j] = encoding[j];
            std::cout << row[j];
        }
        std::cout << std::endl;

        elem = elem->next;
    }

    return encoding_matrix;
}

linkedNode* binaryTree::deep_copy_linked_list(linkedNode* linkedNodeObj) {
    linkedNode* copy_head = new linkedNode;
    copy_head->prev = nullptr;

    linkedNode* original = linkedNodeObj;
    original = original->head();

    linkedNode* copy = copy_head;
    while (original != nullptr) {
        copy->dataNode = original->dataNode;

        if (original->next != nullptr) {
            copy->next = new linkedNode;
            copy->next->prev = copy;

            original = original->next;
            copy = copy->next;
        }
        else{
            copy->next = nullptr;
            break;
        }
    }
    return copy_head;
}

binaryTree::~binaryTree() {
    delete this->leaf_nodes;
    delete this->root;
    delete this->encoding_matrix;
}

/*
 *
 * a b c d e
 *  q c d e
 *  w c e
 *  w r
 *  t
 *
 *         t
 *     w       r
 *   q   d   c   e
 *  a b
 *
 *  a= 000
 *  b= 001
 *  c= 10
 *  d= 01
 *  e= 11
 */

