#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QDebug>
#include <QPair>
#include <QByteArray>

class Node{
    public:
    unsigned char content;  //  Variável que contém o conteúdo do carácter do nó
    int frequency;  //  Variável que contém a frequência do carácter no arquivo
    bool leaf;  //  Variável para determinar se o arquivo é ou não é folha
    Node *left;  //  Variável que realiza as ligações entre os nós
    Node *right;  //  Variável que realiza as ligações entre os nós
    QString code;  //  Variável que contém a codificação do carácter

    Node(unsigned char content = 0, int frequency = 0, bool leaf = 0, Node *left = 0, Node *right = 0);  // Criação do nó com seu conteúdo, frequência, filho esquerdo e filho direito
    QPair<Node*, int> FromByteArray(QByteArray data, int pos);  //  Criação dos nós na reconstrução da árvore
    bool isLeaf();  //  Determina se o nó é uma folha

};
#endif // NODE_H
