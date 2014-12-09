#include "hfile.h"

HFile::HFile()
{
    count = new int[256];
    for(int i = 0; i < 256; i++){
        count[i] = 0;
    }
}

void HFile::openFile()
{
    QFile file("text.txt");

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
}
