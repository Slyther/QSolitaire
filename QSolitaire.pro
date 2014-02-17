#-------------------------------------------------
#
# Project created by QtCreator 2014-02-06T18:20:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSolitaire
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    noded.cpp \
    tdacola.cpp \
    tdalista.cpp \
    qsolitairecard.cpp

HEADERS  += mainwindow.h \
    noded.h \
    tdacola.h \
    tdalista.h \
    qsolitairecard.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
