#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QCoreApplication>
#include <QByteArray>
#include <QList>
#include <iomanip>
#include <sstream>
#include <QDebug>
#include <QString>

#include "node.h"
#include "htree.h"
#include "hfile.h"


bool lessthan(Node* x, Node* y);  //  Função que compara dois nós e retorna o com menor frequência

QByteArray toHex(QByteArray binary);  //  Função que transforma um binário para hexadecimal

QByteArray toChar(QByteArray hex);  //  Função que transforma um hexadecimal em char

unsigned char toByte(QByteArray byteArray);  //  Função que transforma um array de 8 Bytes em 1 Byte

Node* buildTree(int *count);  //  Função que cria a árvore e retorna sua raíz

Node* rebuildTree(QByteArray cod);  //  Função que reconstroi a árvore

void help();  //  Função que imprime a linha de comando

QString getNameIn(QString nameIn);  //  Função que edita o nome do arquivo de entrada

QString getNameOut(QString nameOut);  //  Função que edita o nome do arquivo de saída

bool isDotHuff(QString nameOut);  //  Função que verifica se o nome do arquivo é um .Huff

void compression(QString nameIn, QString nameOut);  //  Função que comprime o arquivo

void uncompression(QString nameFile);  //  Função que descomprime o arquivo nameFile

void uncompression(QString nameFile, QString localOut); //  Função que descomprime o arquivo nameFile na pasta de endereço localOut

#endif // FUNCTIONS_H
