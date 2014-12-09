#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QCoreApplication>
#include <QByteArray>
#include <QList>
#include <QHash>
#include <iomanip>
#include <sstream>
#include <QDebug>
#include <QString>

#include "htree.h"
#include "hfile.h"
#include "node.h"

bool lessthan(Node* x, Node* y);  //  Função que compara dois nós e retorna o com menor frequência

QByteArray toHex(QByteArray binary);  //  Função que transforma um binário para hexadecimal

QByteArray toChar(QByteArray hex);  //  Função que transforma um hexadecimal em char

unsigned char toByte(QByteArray byteArray);  //  Função que transforma um array de 8 Bytes em 1 Byte

Node* buildTree(int *count);  //  Função que cria a árvore e retorna sua raíz

void compression();  //  Função que comprime o arquivo

void uncompression();  //  Função que descomprime a árvore


#endif // FUNCTIONS_H
