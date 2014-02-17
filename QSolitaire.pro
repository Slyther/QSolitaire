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
    tdalista.cpp \
    qsolitairecard.cpp \
    qcardlist.cpp

HEADERS  += mainwindow.h \
    noded.h \
    tdalista.h \
    qsolitairecard.h \
    qcardlist.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
