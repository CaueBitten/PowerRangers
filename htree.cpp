#include "htree.h"

void HTree::toString(Node *node, QString &str){
    if(node != 0){
        str.append("\n");
        str.append(QString("%1").arg(node->content));
        toString(node->left, str);
        toString(node->right, str);
    }
}

void HTree::toHuffman(Node *node){
    if(!node->isLeaf()){
        m_treeCode += "(";
        if(node->left){
            node->left->code = node->code + "0";
            m_listCodes[node->left->content] = node->left->code;
        }
        if(node->right){
            node->right->code = node->code + "1";
            m_listCodes[node->right->content] = node->right->code;
        }

        toHuffman(node->left);
        toHuffman(node->right);
    }
    else{
        if(node->content == 40 || node->content == 42){
            m_treeCode += "*";
        }
        m_treeCode += node->content;
    }
}

void HTree::toTree(Node *node)
{

}

HTree::HTree(){
    m_root = 0;
    m_cursor = m_root;
    m_listCodes = new QString[256];
}

HTree::HTree(QByteArray treeCode){
    m_root = 0;
    m_cursor = m_root;
    m_listCodes = new QString[256];
    m_treeCode = treeCode;
}

HTree::HTree(Node *cell){
    m_root = cell;
    m_cursor = m_root;
    m_listCodes = new QString[256];
}
Node* HTree::add(Node *cell_one, Node *cell_two){
    Node *mother = new Node(0, cell_one->frequency + cell_two->frequency, cell_one, cell_two);
    return mother;
}

Node* HTree::getTree(){
    return(m_root);
}

void HTree::toLeft(){
    m_cursor = m_cursor->left;
}

void HTree::toRight(){
    m_cursor = m_cursor->right;
}

QString HTree::toString(){
    QString str;
    toString(m_root, str);
    return(str);
}

void HTree::toHuffman(){
    toHuffman(m_root);
}

QByteArray HTree::getTreeCode(){
    return m_treeCode;
}

void HTree::encodingFile(QByteArray copyFiles)
{
    for(int i = 0; i < copyFiles.size(); i++){

    }
}

