#include "functions.h"

bool lessthan(Node* x, Node* y){
    if(x->frequency == y->frequency){
        return (x->content < y->content);
    }
    return (x->frequency < y->frequency);
}

QByteArray toHex(QByteArray binary){
    QByteArray hex;
        if(binary == "0000") hex.append("0");
        if(binary == "0001") hex.append("1");
        if(binary == "0010") hex.append("2");
        if(binary == "0011") hex.append("3");
        if(binary == "0100") hex.append("4");
        if(binary == "0101") hex.append("5");
        if(binary == "0110") hex.append("6");
        if(binary == "0111") hex.append("7");
        if(binary == "1000") hex.append("8");
        if(binary == "1001") hex.append("9");
        if(binary == "1010") hex.append("A");
        if(binary == "1011") hex.append("B");
        if(binary == "1100") hex.append("C");
        if(binary == "1101") hex.append("D");
        if(binary == "1110") hex.append("E");
        if(binary == "1111") hex.append("F");
    return hex;
}

QByteArray toChar(QByteArray hex){
    QByteArray aux;
    QByteArray finalChar;
    for(int i = 0; i < hex.size(); i += 2){
        aux.append(hex.at(i));
        aux.append(hex.at(i+1));
        finalChar.append(aux);
        unsigned char tmp = finalChar.at(i/2);
        finalChar.remove(i/2, 1);
        finalChar.insert(i/2, tmp);
        aux.clear();
    }
    return finalChar;
}

unsigned char toByte(QByteArray byteArray)
{
    unsigned char myByte = 0;
    unsigned char mask = 0x1;
    for(int i = 7; i >= 0  ; i--){
        if(byteArray.at(i) == '1'){
            mask = 0x1 << (7-i);
            myByte += mask;
        }
    }
    return myByte;
}

Node* buildTree(int *count)
{
    QList<Node*> list;

    for(int i = 0; i < 256; i++){
        if(count[i]){
            list.append(new Node(i, count[i], 0, 0));
        }
    }

    while(list.length() != 1){
        qSort(list.begin(), list.end(), lessthan);
        Node *mother = new Node(0, list.at(0)->frequency + list.at(1)->frequency, list.at(0), list.at(1));
        list.removeAt(0);
        list.removeAt(0);
        list.append(mother);
    }

    return list.at(0);
}

Node* rebuildTree(QByteArray cod){
    Node* node = new Node();
    node = node->FromByteArray(cod, 0).first;
    return node;
}

void compression(QString nameIn, QString nameOut)
{
    // Manipulador do arquivo
    HFile *file = new HFile();
    // Arvore de Huffman
    HTree *tree;

    // Lê o arquivo e conta a frequência dos bytes
    file->openFile(nameIn);

    // Cria a árvore de Huffman
    tree = new HTree(buildTree(file->count));
    tree->toHuffman();
    tree->encodingFile(file->copyFile);
    tree->trashCode();
    tree->sizeTree();
    file->buildHuffmanFile(tree->finalCode(tree->sizeName(nameIn), nameIn), nameOut);

    qDebug() << "Arquivo comprimido com sucesso!" ;
}

void uncompression(QString nameFile)
{
    // Manipulador do arquivo
    HFile *file = new HFile();
    // Árvore de Huffman
    HTree *tree = new HTree();
    // Lê o arquvio .huff
    file->openFilesimple(nameFile);
    qDebug() << "1";
    tree->getSizeThings(file->copyFile);
    qDebug() << "1";
    tree->setRoot(rebuildTree(tree->my_treeCode));
    qDebug() << "1";
    tree->setFileOut();
    qDebug() << "1";
    file->rebuildFile(tree->my_fileName, tree->my_finalOutPut);

    qDebug() << "Arquivo compactado com sucesso!";
}

void uncompression(QString nameFile, QString localOut)
{
    // Manipulador do arquivo
    HFile *file = new HFile();
    // Árvore de Huffman
    HTree *tree = new HTree();
    // Lê o arquvio .huff
    file->openFilesimple(nameFile);

    tree->getSizeThings(file->copyFile);

    qDebug() << tree->s_Trash;
    qDebug() << tree->s_Tree;
    qDebug() << tree->s_Name;
    qDebug() << tree->my_fileName;;
    qDebug() << tree->my_treeCode;
    qDebug() << tree->my_preCode;

    //qDebug() << tree->my_finalOutPut;
}


void help(){
    QString help;

    help = "HELP:\n";
    help += "COMO USAR A LINHA DE COMANDO:\n";
    help += "1 -- $> huffman -c arquivo_origem.x -o arquivo_de_saida.huff\n";
        help += "       Comprime o arquivo 'arquivo_origem.x' e gera o arquivo de saída  'arquivo_de_saida.huff'\n";
    help += "2 -- $> huffman -c arquivo.x\n";
        help += "       Comprime o arquivo 'arquivo.x' e gera o arquivo de saída  'arquivo.huff', mantendo o nome do arquivo original\n";
    help += "3 -- $> huffman arquivo.huf\n";
        help += "       Descomprime o arquivo 'arquivo.huff' na pasta local com o nome original\n";
    help += "4 -- $> $> huffman arquivo.huff -d /home/user/destino\n";
        help += "       Descomprime o arquivo 'arquivo.huff' na pasta '/home/user/destino' com o nome original\n";
    ;

    qDebug() << qPrintable(help);
}


//QString getNameIn(QString nameIn)
//{

//}


QString getNameOut(QString nameOut)
{
    QString nameFileOut;
    int i;
    for(i = nameOut.size()-1 ; i > 0 && nameOut.at(i)!= '/'; i--);
    if(i > 0 && nameOut.at(i) == '/') {
        i++;
    }
    for( ; i < nameOut.size() && nameOut.at(i) != '.'; i++) {
         nameFileOut.append(nameOut.at(i));
    }
    nameFileOut += ".huff";
    return nameFileOut;
}

bool isDotHuff(QString nameOut){

    QString typeFileOut;
    int i;
    for(i = nameOut.size()-1 ; i > 0 && nameOut.at(i)!= '/'; i--);
    if(i > 0 && nameOut.at(i) == '/') i++;
    for( ; i < nameOut.size() && nameOut.at(i) != '.'; i++);
    if(i < nameOut.size() && nameOut.at(i) == '.') i++;
    for(; i < nameOut.size(); i++){
        typeFileOut.append(nameOut.at(i));
    }
    if(typeFileOut == "huff"){
        return true;
    }
    qDebug() << "ERRO: O ARQUIVO NAO EH DO TIPO '.huff'\n";
    return false;
}
