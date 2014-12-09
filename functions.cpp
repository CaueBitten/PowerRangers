#include "functions.h"

bool lessthan(Node* x, Node* y){
    if(x->frequency == y->frequency){
        return (x->content < y->content);
    }
    return (x->frequency < y->frequency);
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
    HFile *fileIn = new HFile();
    // Arvore de Huffman
    HTree *tree;
    // Código do arquivo de saída
    QByteArray fileOut;


    // Lê o arquivo e conta a frequência dos bytes
    fileIn->openFile();
    // Cria a árvore de Huffman
    tree = new HTree(buildTree(fileIn->count));
    tree->toHuffman();
    qDebug() << tree->getTreeCode();
}

void uncompression()
{

}
