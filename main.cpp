#include <QCoreApplication>
#include "functions.h"

int main(int argc, char *argv[])
{
    for(int i= 0; i < argc; ++i){
        qDebug() << argv[i];
    }
    //QCoreApplication a(argc, argv);
    compression();
    qDebug() << "AQUI";
    return /*a.exec()*/ 0;
}
