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

//void HTree::toTree(Node *node)
//{
//    if(m_treeCode.at(0) == '*'){
//        m_treeCode.remove(0,1);
//    }
//    else if(m_treeCode.at(0) == '('){

//    }
//}

HTree::HTree(){
    m_root = 0;
    m_cursor = m_root;
    m_listCodes = new QString[256];
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
    return;
}

QByteArray HTree::getTreeCode(){
    return m_treeCode;
}

void HTree::encodingFile(QByteArray copyFiles)
{
    for(int i = 0; i < copyFiles.size(); i++){
        m_fileCode.append(m_listCodes[copyFiles.at(i)]);
    }
}

QByteArray HTree::getFileCode()
{
    return m_fileCode;
}

QByteArray HTree::trashCode()
{
    QByteArray tmp;
    int trash = (m_fileCode.size())%8;
    char aux[3];

    itoa(trash, aux, 2);
    tmp.append(aux);

    for(int i = 0; i < 3 - tmp.size(); i++){
        m_sizeTrash.append("0");
    }
    m_sizeTrash.append(aux);

    for(int i = 0; i < trash; i++){
        m_fileCode.append('0');
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
            head.append(toByte(tmp));
            tmp.clear();
        }
    }
    /* Fim da Setação dos dois primeiros bytes do cabeçalho*/

    /* Início da Setação do terceiro byte do cabeçalho */
    name.append(toByte(sizeName));
    name.append(fileName);
    /* Fim da Setação do terceiro byte do cabeçalho */
    aux = m_fileCode;
    for(int i = 0; i < m_fileCode.size(); i++){
        tmp.append(aux.at(i));
        if(i%8 == 7 && i > 0){
            code.append(toByte(tmp));
            qDebug() <<"code" << i/8 << hex << (unsigned char) code.at(i/8) ;
            tmp.clear();
        }
    }

    /* Início da Setação dos bytes do código no cabeçalho */

    /* Fim da Setação dos bytes do código no cabeçalho */

//    for(int i = 0; i < 16; i += 4){
//        for(int j = 0; j < 4; j++){
//            aux.append(m_sizeTrash.at(j+i));
//        }
//        head.append(toHex(aux));
//        aux.clear();
//    }

//    head = toChar(head);

//    for(int i = 0; i < 8; i += 4){
//        for(int j = 0; j < 4; j++){
//            aux.append(sizeName.at(j+i));
//        }
//        name.append(toHex(aux));
//        aux.clear();
//    }
//    name.append(fileName);

//    for(int i = 0; i < m_fileCode.size(); i += 4){
//        for(int j = 0; j < 4; j++){
//            aux.append(m_fileCode.at(j+i));
//        }
//        code.append(toHex(aux));
//        aux.clear();
//    }


    m_fileOut.append(head);
    m_fileOut.append(name);
    m_fileOut.append(m_treeCode);
    m_fileOut.append(code);

    return m_fileOut;
}

