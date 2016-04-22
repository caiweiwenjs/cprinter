#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T15:11:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FirstQtProject
TEMPLATE = app

CONFIG += c++11
#QMAKE_CFLAGS += `cups-config --cflags`
QMAKE_CXXFLAGS += `cups-config --cflags`
LIBS += `cups-config --libs`

SOURCES += main.cpp\
        mainwindow.cpp \
    unixsocket.cpp \
    server.cpp \
    sqlhelper.cpp \
    prtselectdialog.cpp \
    cupsutil.cpp

HEADERS  += mainwindow.h \
    unixsocket.h \
    server.h \
    sqlhelper.h \
    prtselectdialog.h \
    cupsutil.h

FORMS    += mainwindow.ui \
    prtselectdialog.ui
