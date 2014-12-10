#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T12:37:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Huffman
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    htree.cpp \
    hfile.cpp \
    node.cpp \
    functions.cpp

HEADERS  += gui.h \
    htree.h \
    hfile.h \
    node.h \
    functions.h

FORMS    += gui.ui
