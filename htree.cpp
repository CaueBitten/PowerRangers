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
            m_listCodes[(unsigned char)node->left->content] = node->left->code;
        }
        if(node->right){
            node->right->code = node->code + "1";
            m_listCodes[(unsigned char)node->right->content] = node->right->code;
        }

        toHuffman(node->left);
        toHuffman(node->right);
    }
    else{
        if((unsigned char)node->content == 40 || (unsigned char)node->content == 42){
            m_treeCode += "*";
        }
        m_treeCode += (unsigned char) node->content;
    }
}

HTree::HTree(){
    m_root = 0;
    m_cursor = m_root;
    m_listCodes = new QString[256];
    s_Trash = 0;
    s_Tree = 0;
    s_Name = 0;
}

HTree::HTree(QByteArray treeCode){
    m_root = 0;
    m_cursor = m_root;
    m_listCodes = new QString[256];
    m_treeCode.append(treeCode);
}

HTree::HTree(Node *cell){
    m_root = cell;
    m_cursor = m_root;
    m_listCodes = new QString[256];
}

void HTree::setRoot(Node *root)
{
    m_root = root;
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
    return;
}

QByteArray HTree::getTreeCode(){
    return m_treeCode;
}

void HTree::encodingFile(QByteArray copyFiles)
{
    for(int i = 0; i < copyFiles.size(); i++){
        m_fileCode.append(m_listCodes[(unsigned char)copyFiles.at(i)]);
    }
}

QByteArray HTree::getFileCode()
{
    return m_fileCode;
}

QByteArray HTree::trashCode()
{
    QByteArray tmp;
    int trash = 8 - (m_fileCode.size())%8;
    char aux[3];

    itoa(trash, aux, 2);
    tmp.append(aux);

    for(int i = 0; i < 3 - tmp.size(); i++){
        m_sizeTrash.append("0");
    }
    m_sizeTrash.append(aux);

    for(int i = 0; i < trash; i++){
        m_fileCode += '0';
    }

    return m_sizeTrash;
}

QByteArray HTree::sizeTree()
{
    char aux[13];
    QByteArray tmp;
    itoa(m_treeCode.size(), aux, 2);

    m_sizeTree.append(aux);

    for(int i = 0; i < 13 - m_sizeTree.size(); i++){
        tmp.append("0");
    }

    tmp.append(m_sizeTree);
    m_sizeTree = tmp;

    return m_sizeTree;
}

QByteArray HTree::sizeName(QString nameFile)
{
    QByteArray nameFileReturn;
    QByteArray tmp;
    int length = nameFile.size();
    char aux[8];

    itoa(length, aux, 2);
    tmp.append(aux);

    for(int i = 0; i < 8 - tmp.size(); i++){
        nameFileReturn.append("0");
    }

    nameFileReturn.append(aux);

    return nameFileReturn;
}

QByteArray HTree::finalCode(QByteArray sizeName, QString fileName)
{
    QByteArray aux;
    QByteArray tmp;
    QByteArray head;
    QByteArray name;
    QByteArray code;

    /* Início da Setação dos dois primeiros bytes do cabeçalho*/
    aux = m_sizeTrash.append(m_sizeTree);
    for(int i = 0; i < 16; i++){
        tmp.append(aux.at(i));
        if(i%8 == 7 && i > 0){
            head.append((unsigned char)toByte(tmp));
            tmp.clear();
        }
    }
    /* Fim da Setação dos dois primeiros bytes do cabeçalho*/

    /* Início da Setação do terceiro byte do cabeçalho */
    name.append(toByte(sizeName));
    name.append(fileName);
    /* Fim da Setação do terceiro byte do cabeçalho */

    /* Início da Setação dos bytes do código no cabeçalho */
    aux = m_fileCode;
    for(int i = 0; i < m_fileCode.size(); i++){
        tmp.append((unsigned char)aux.at(i));
        if(i%8 == 7 && i > 0){
            code.append((unsigned char)toByte(tmp));
            tmp.clear();
        }
    }
    /* Fim da Setação dos bytes do código no cabeçalho */



    m_fileOut.append(head);
    m_fileOut.append(name);
    m_fileOut.append(m_treeCode);
    m_fileOut.append(code);

    return m_fileOut;
}

bool HTree::getBit(long long pos)
{
    unsigned char byte = (unsigned char) my_fileCode.at(pos/8);
    unsigned char mask = 0x1;
    mask = mask << (7 - pos%8);
    byte = byte & mask;
    if(byte){
        return true;
    }
    return false;
}

void HTree::getSizeThings(QByteArray code)
{
    my_fileCode = code;
    for(int i = 0; i < 24; i++){
        if(i <= 2){
            if(getBit(i)){
                s_Trash += 0x1 << (2-i);
            }
        }
        else if(i <= 15){
            if(getBit(i)){
                s_Tree += 0x1 << (15-i);
            }
        }
        else{
            if(getBit(i)){
                s_Name += 0x1 << (23-i);
            }
        }
    }
    for(int i = 3; i < 3 + s_Name; i++){
        my_fileName += (unsigned char)my_fileCode.at(i);
    }
    for(int i = 3 + s_Name; i < 3 + s_Name + s_Tree; i++){
        my_treeCode.append((unsigned char)my_fileCode.at(i));
    }
    for(int i = 3*8 + s_Name*8 + s_Tree*8; i < ((my_fileCode.size())*8 - s_Trash); i++){
        if(getBit(i)){
            my_preCode += '1';
        }
        else{
            my_preCode += '0';
        }
    }
}

void HTree::setFileOut(){
    m_cursor = m_root;
    for(int i = 0; i < my_preCode.size(); i++){
        if((unsigned char)my_preCode.at(i) ==  '0'){
            toLeft();
        }
        else if((unsigned char)my_preCode.at(i) == '1'){
            toRight();
        }
        if(m_cursor->isLeaf()){
            my_finalOutPut.append((unsigned char)m_cursor->content);
            m_cursor = m_root;
        }
    }
}
