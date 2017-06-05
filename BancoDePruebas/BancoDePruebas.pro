#-------------------------------------------------
#
# Project created by QtCreator 2015-04-24T12:25:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BancoDePruebas
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    leer.cpp \
    song.cpp \
    copiar.cpp \
    organizar.cpp

HEADERS  += mainwindow.h \
    leer.h \
    song.h \
    copiar.h \
    organizar.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -ltag
