#ifndef HFILE_H
#define HFILE_H

#include <QFile>
#include <QDebug>
#include <QByteArray>

class HFile
{
public:
    int *count;  //  Variável quem armazerna a frequência de cada elemento
    QByteArray copyFile;  //  Variável que armazena uma cópia do arquivo
    QString nameFile;  //  Variável que armazena o nome do arquivo

    HFile();
    ~HFile();

    void openFile();  //  Abre o arquivo e faz a contagem de cada elemento.
    void buildHuffmanFile(QByteArray codeFile, QString nameFile);  //  Cria o arquivo com a codificação já pronta

};

#endif // HFILE_H
