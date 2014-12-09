#ifndef HTREE_H
#define HTREE_H

#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QList>
#include <algorithm>

#include "node.h"

class HTree
{
private:
    Node *m_cursor;  //  Cursor que navega pela árvore
    Node *m_root;  //  Raíz da árvore
    QString* m_listCodes;  // Array que contem os códigos dos bytes
    QByteArray m_treeCode;  //  Variável que contém a árvore codificada
    QByteArray m_fileCode;  //  Variável que contém o arquivo codificado

    void toString(Node *node, QString &str);  //  Função para imprimir a árvore
    void toHuffman(Node *node);  //  Função para setar a codificação da árvore e a lista dos códigos dos bytes
    void toTree(Node *node);  //  Função para reconstruir a árvore

public:

    HTree();
    HTree(Node *cell);
    HTree(QByteArray treeCode);
    Node* add(Node *cell_one, Node *cell_two);  //  Adciona um nó na árvore
    Node* getTree();  //  Retorna o a raiz da árvore
    void toLeft();  //  Faz o cursor se deslocar para o nó da esquerda
    void toRight();  // Faz o cursor se deslocar para o nó da direita
    QString toString();  //  Retorna a árvore impressa
    void toHuffman();  //  Seta a codificação da árvore e seta o nosso listCodes
    QByteArray getTreeCode(); //  Retorna a codificação da árvore.
    void encodingFile(QByteArray copyFiles);  //  Codifica o arquivo

};

#endif // HTREE_H
