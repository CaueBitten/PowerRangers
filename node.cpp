#include "node.h"

Node::Node(unsigned char content, int frequency, Node *left, Node *right){
    this->content = content;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

bool Node::isLeaf()
{
    if(this->left == 0 && this->right == 0){
        return true;
    }
    return false;
}
