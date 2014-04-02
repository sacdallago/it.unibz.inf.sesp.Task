#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T11:25:11
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktop
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    connection.cpp \
    task.cpp \
    taskutilities.cpp \
    utilities.cpp \
    collection.cpp

HEADERS  += widget.h \
    connection.h \
    task.h \
    taskutilities.h \
    utilities.h \
    collection.h

FORMS    += widget.ui
