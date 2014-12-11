#include "functions.h"

bool lessthan(Node* x, Node* y){
    if(x->frequency == y->frequency){
        return (x->content < y->content);
    }
    return (x->frequency < y->frequency);
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
            list.append(new Node((unsigned char) i, count[i], 0, 0));
        }
    }

    while(list.length() != 1){
        qSort(list.begin(), list.end(), lessthan);
        Node *mother = new Node(0, list.at(0)->frequency + list.at(1)->frequency, 0, list.at(0), list.at(1));
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
    if(!file->copyFile.size()){
        qDebug() << "ARQUIVO VAZIO!";
        return;
    }

    // Cria a árvore de Huffman
    tree = new HTree(buildTree(file->count));
    tree->toHuffman();
    tree->encodingFile(file->copyFile);
    tree->trashCode();
    tree->sizeTree();
    tree->showListCode();
    QByteArray codeHuffOut = tree->finalCode(tree->sizeName(nameIn), nameIn);
    file->buildHuffmanFile(codeHuffOut, nameOut);

    qDebug() << "Arquivo compactado com sucesso!" ;
}

void uncompression(QString nameFile)
{
    // Manipulador do arquivo
    HFile *file = new HFile();
    // Árvore de Huffman
    HTree *tree = new HTree();

    // Lê o arquvio .huff
    file->openFilesimple(nameFile);
    tree->getSizeThings(file->copyFile);

    if(!tree->my_fileName.size() || !tree->my_treeCode.size()){
        qDebug() << "ARQUIVO CORROMPIDO!";
        return;
    }

//    tree->setRoot(rebuildTree(tree->my_treeCode));
//    tree->setFileOut();

//    qDebug() << tree->s_Trash << tree->s_Name << tree->s_Tree;
//    qDebug() << tree->my_treeCode;
//    qDebug() << tree->my_finalOutPut;


    file->rebuildFile(tree->my_fileName, tree->my_finalOutPut);

    qDebug() << "Arquivo descompactado com sucesso!";
}

void uncompression(QString nameFile, QString localOut)
{
    // Manipulador do arquivo
    HFile *file = new HFile();
    HFile *fileOut = new HFile();
    // Árvore de Huffman
    HTree *tree = new HTree();

    // Lê o arquvio .huff
    file->openFilesimple(nameFile);
    tree->getSizeThings(file->copyFile);

    if(!tree->my_fileName.size() || !tree->my_treeCode.size()){
        qDebug() << "ARQUIVO CORROMPIDO!";
        return;
    }

    tree->setRoot(rebuildTree(tree->my_treeCode));
    tree->setFileOut();
    localOut.append(tree->my_fileName);

    fileOut->rebuildFile(localOut, tree->my_finalOutPut);

    qDebug() << "Arquivo descompactado com sucesso!";
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
    if(i > 0 && nameOut.at(i) == '/'){
        i++;
    }
    for( ; i < nameOut.size() && nameOut.at(i) != '.'; i++);
    if(i < nameOut.size() && nameOut.at(i) == '.'){
        i++;
    }
    for(; i < nameOut.size(); i++){
        typeFileOut.append(nameOut.at(i));
    }
    if(typeFileOut == "huff"){
        return true;
    }
    qDebug() << "ERRO: O ARQUIVO NAO EH DO TIPO '.huff'\n";
    return false;
}


QString getNameIn(QString nameIn)
{
    QString nameFileIn;
    int i;
    for(i = nameIn.size()-1 ; i > 0 && nameIn.at(i)!= '/'; i--);
    if(i > 0 && nameIn.at(i) == '/'){
        i++;
    }
    for(; i < nameIn.size(); i++){
        nameFileIn.append(nameIn.at(i));
    }
    return nameFileIn;
}
