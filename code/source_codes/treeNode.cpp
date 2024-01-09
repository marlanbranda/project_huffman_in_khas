#include "../header_files/treeNode.h"

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
//    this->symbol;
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

// just swaps the datanodes inside LN objects
// create_tree is dependent on this implementation
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

void encoding_struct::print_encoding_struct() {
    std::cout << (int)(unsigned char)this->symbol << '\t' << this->binary_encoding << std::endl;
}

binaryTree::binaryTree(freqTable* freqObj) {
    this->leaf_nodes = create_linked_node(freqObj);
    this->root = create_tree((this->leaf_nodes));
    this->encoding_matrix = create_encoding_matrix();
}

// for each symbol and frequency creates treeNode and put it inside a linked node
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

// creates a deep copy
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

encoding_struct* binaryTree::create_encoding_matrix() {

    linkedNode* elem = this->leaf_nodes;
    int len_of_leaves = elem->length();

    encoding_struct* encoding_matrix = new encoding_struct[len_of_leaves];
    auto p = encoding_matrix;
    for(int i=0; i < len_of_leaves; i++) {
        p->symbol = elem->dataNode->symbol;

        treeNode* currNode = elem->dataNode;
        do{
            treeNode* parentNode = currNode->parent;
            if (currNode == parentNode->left) { // NOLINT(*-branch-clone)
                p->binary_encoding = '0' + p->binary_encoding;
            } else {
                p->binary_encoding = '1' + p->binary_encoding;
            }
            currNode = parentNode;
        }while(currNode != this->root);

        p++;
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

void binaryTree::delete_whole_tree(treeNode* root) { // NOLINT(*-no-recursion)
    if (root == nullptr) {
        return;
    }

    delete_whole_tree(root->left);
    delete_whole_tree(root->right);
    delete root;
    root = nullptr;
}

binaryTree::~binaryTree() {
    linkedNode* currLN = this->leaf_nodes;
    linkedNode* nextLN;

    while(currLN->next != nullptr){
        nextLN = currLN->next;
        delete currLN;
        currLN = nextLN;
    }
    delete currLN;
    this->leaf_nodes = nullptr;

    delete_whole_tree(this->root);

    delete[] this->encoding_matrix;
    this->encoding_matrix = nullptr;
}

