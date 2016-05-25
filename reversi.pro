#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T23:30:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reversi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        boardview.cpp\
        virtual_board.cpp\
        newGameDialog.cpp

HEADERS  += mainwindow.h newgamedialog.h boardview.h virtual_board.h

FORMS    += mainwindow.ui \
    ui/newgamedialog.ui

CONFIG += c++11
