#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QDebug>
#include <QPair>
#include <QByteArray>

class Node{
    public:
    unsigned char content;
    int frequency;
    bool leaf;
    Node *left;
    Node *right;
    QString code;

    Node(unsigned char content = 0, int frequency = 0, bool leaf = 1, Node *left = 0, Node *right = 0);  // Criação do nó com seu conteúdo, frequência, filho esquerdo e filho direito
    QPair<Node*, int> FromByteArray(QByteArray data, int pos);
    bool isLeaf();  //  Determina se o nó é uma folha

};
#endif // NODE_H
