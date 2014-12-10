#include "node.h"

Node::Node(unsigned char content, int frequency, Node *left, Node *right){
    this->content = content;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

QPair<Node*, int> Node::FromByteArray(QByteArray data, int pos){
    char current = data.at(pos);
    if(current != 0x28){
        if(current == 0x2A){
            pos++;
            current = data.at(pos);
        }
        qDebug() << current;
        return QPair<Node*, int> (new Node(current,0,0,0), pos);
    }
    QPair<Node*, int> left = this->FromByteArray(data, pos+1);
    QPair<Node*, int> right = this->FromByteArray(data, left.second +1);
    Node* node = new Node(0x28,0, left.first, right.first);
    return QPair<Node*, int> (node , right.second);
}

bool Node::isLeaf()
{
    if(this->left == 0 && this->right == 0){
        return true;
    }
    return false;
}
