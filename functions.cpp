#include "functions.h"

bool lessthan(Node* x, Node* y){
    if(x->frequency == y->frequency){
        return (x->content < y->content);
    }
    return (x->frequency < y->frequency);
}

QByteArray toHex(QByteArray binary){
    QByteArray hex;
        if(binary == "0000") hex.append("0");
        if(binary == "0001") hex.append("1");
        if(binary == "0010") hex.append("2");
        if(binary == "0011") hex.append("3");
        if(binary == "0100") hex.append("4");
        if(binary == "0101") hex.append("5");
        if(binary == "0110") hex.append("6");
        if(binary == "0111") hex.append("7");
        if(binary == "1000") hex.append("8");
        if(binary == "1001") hex.append("9");
        if(binary == "1010") hex.append("A");
        if(binary == "1011") hex.append("B");
        if(binary == "1100") hex.append("C");
        if(binary == "1101") hex.append("D");
        if(binary == "1110") hex.append("E");
        if(binary == "1111") hex.append("F");
    return hex;
}

QByteArray toChar(QByteArray hex){
    QByteArray aux;
    QByteArray finalChar;
    for(int i = 0; i < hex.size(); i += 2){
        aux.append(hex.at(i));
        aux.append(hex.at(i+1));
        finalChar.append(aux);
        unsigned char tmp = finalChar.at(i/2);
        finalChar.remove(i/2, 1);
        finalChar.insert(i/2, tmp);
        aux.clear();
    }
    return finalChar;
}

unsigned char toByte(QByteArray byteArray)
{
    unsigned char myByte = 0;
    unsigned char mask = 0x1;
    for(int i = 7; i >= 0  ; i--){
        if(byteArray.at(i) == '1'){
            mask = 0x1 << 7-i;
            myByte += mask;
        }
    }
    return myByte;
}

Node* buildTree(int *count)
{
    QList<Node*> list;

    for(int i = 0; i < 256; i++){
        if(count[i]){
            list.append(new Node(i, count[i], 0, 0));
        }
    }

    while(list.length() != 1){
        qSort(list.begin(), list.end(), lessthan);
        Node *mother = new Node(0, list.at(0)->frequency + list.at(1)->frequency, list.at(0), list.at(1));
        list.removeAt(0);
        list.removeAt(0);
        list.append(mother);
    }

    return list.at(0);
}
void compression()
{
    // Manipulador do arquivo
    HFile *file = new HFile();
    // Arvore de Huffman
    HTree *tree;

    // Lê o arquivo e conta a frequência dos bytes
    file->openFile();
    // Cria a árvore de Huffman
    tree = new HTree(buildTree(file->count));
    tree->toHuffman();
    tree->encodingFile(file->copyFile);
    //tree->getTreeCode();
    //tree->getFileCode();
    qDebug() << tree->trashCode();
    qDebug() << tree->getFileCode();
    qDebug() << tree->sizeTree();
    qDebug() << tree->sizeName((QString)"text.txt");
    file->buildHuffmanFile(tree->finalCode(tree->sizeName((QString)"text.txt"), (QString)"text.txt"), (QString)"text.txt");
}

void uncompression()
{

}


