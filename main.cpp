#include <QApplication>
#include "functions.h"
#include "gui.h"


int main(int argc, char *argv[])
{
    QList<QString> arg;
    for(int i = 0; argv[i]; i++){
        arg += argv[i];
    }


    if(argc == 3 && arg[1] == "-c") {
        QString nameFile = arg[2];
        compression(nameFile, getNameOut(nameFile));
    }

    else if(argc == 5 && arg[1] == "-c" && arg[3] == "-o"){
        QString nameFileIn = arg[2];
        QString nameFileOut = arg[4];
        if(isDotHuff(nameFileOut)){
            compression(nameFileIn, nameFileOut);
        }
        else{
            help();
        }
    }

    else if(argc == 2 && arg[1] != "--gui"){
        QString nameFile = arg[1];
        if(isDotHuff(nameFile)){
            uncompression(nameFile);
        }
        else{
            qDebug() << "O arquivo não é do tipo .huff";
            help();
        }
    }

    else if(argc == 4 && arg[2] == "-d"){
        QString nameFile = arg[1];
        QString localOut = arg[3];
        if(localOut.size() && localOut[localOut.size()-1] != '/') localOut += '/';

        if(isDotHuff(nameFile)){
            uncompression(nameFile, localOut);
        }
        else{
            qDebug() << "O arquivo não é do tipo .huff";
            help();
        }
    }

    else if(argc == 2 && arg[1] == "--gui"){
        QApplication a(argc, argv);
        Gui w;
        w.show();
        return a.exec();
    }

    else if(argc == 2 && (arg[1] == "-h" || arg[1] == "-help")){
        help();
    }

    else if(argc == 3 && arg[1] == "-com"){
        QString nameFile = arg[2];
        QString nameFileOut = getNameOut(nameFile);
        compression(nameFile, nameFileOut);
        compression(nameFileOut, nameFileOut);
    }

    else if(argc == 3 && arg[1] == "-decom"){
        QString nameFile = arg[2];
        if(isDotHuff(nameFile)){
            uncompression(nameFile);
            if(isDotHuff(nameFile)){
                uncompression(nameFile);
            }
            else{
                qDebug() << "O arquivo não foi comprimido duplamente";
            }
        }
        else{
            qDebug() << "O arquivo não é do tipo .huff";
            help();
        }
    }

    else{
        qDebug() << "COMANDO INVALIDO!\n";
        help();
    }
    return 0;
}
