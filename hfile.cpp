#include "hfile.h"

HFile::HFile()
{
    count = new int[256];
    for(int i = 0; i < 256; i++){
        count[i] = 0;
    }
}

void HFile::openFile(QString nameFile)
{
    QFile file(nameFile);

    //Termina a função caso o arquivo não abra
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "The file could not be read.";
        return;
    }


    //Ler o arquivo e conta a frequência de cada caracter.
    while (!file.atEnd()) {
        QByteArray line = file.readLine(1024);
        copyFile.append(line);
        for(int i = 0; i < line.size(); ++i){
            ++count[(unsigned char)line[i]];
        }
    }
    file.close();
}

void HFile::buildHuffmanFile(QByteArray codeFile, QString nameFile)
{
    QFile file(nameFile);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "The file could not be write";
        return;
    }

    file.write(codeFile);
    file.close();
}

void HFile::openFilesimple(QString nameIn)
{
    QFile file(nameIn);

    //Termina a função caso o arquivo não abra
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "The file could not be read.";
        return;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine(1024);
        copyFile.append(line);
    }
    file.close();
}

void HFile::rebuildFile(QString name, QByteArray code)
{
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "The file could not be write";
        return;
    }
    file.write(code);
    file.close();
}
