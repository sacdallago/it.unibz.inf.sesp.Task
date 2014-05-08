#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T11:25:11
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktop
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    connection.cpp \
    task.cpp \
    taskutilities.cpp \
    utilities.cpp \
    collection.cpp \
    mainwindow.cpp \
    addtaskdialog.cpp \
    aboutdialog.cpp \
    taskwidget.cpp \
    taskdatabase.cpp \
    relations.cpp \
    moredialog.cpp \
    logindialog.cpp \
    tests/mainwindowtest.cpp \
    tests/collectiontest.cpp

HEADERS  += widget.h \
    connection.h \
    task.h \
    taskutilities.h \
    utilities.h \
    collection.h \
    mainwindow.h \
    addtaskdialog.h \
    aboutdialog.h \
    taskwidget.h \
    taskdatabase.h \
    relations.h \
    moredialog.h \
    logindialog.h \
    tests/AutoTest.h \
    tests/mainwindowtest.h \
    tests/collectiontest.h

FORMS    += widget.ui \
    mainwindow.ui \
    addtaskdialog.ui \
    aboutdialog.ui \
    taskwidget.ui \
    relations.ui \
    moredialog.ui \
    logindialog.ui

CONFIG += c++11

RESOURCES += \
    images.qrc

OTHER_FILES += \
    Database.txt
