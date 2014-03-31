#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T11:25:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktop
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    task.cpp \
    connection.cpp

HEADERS  += widget.h \
    task.h \
    connection.h \
    mysql_connection.h \
    mysql_driver.h \
    mysql_error.h \
    cppconn/build_config.h \
    cppconn/config.h \
    cppconn/connection.h \
    cppconn/datatype.h \
    cppconn/driver.h \
    cppconn/exception.h \
    cppconn/metadata.h \
    cppconn/parameter_metadata.h \
    cppconn/prepared_statement.h \
    cppconn/resultset.h \
    cppconn/resultset_metadata.h \
    cppconn/sqlstring.h \
    cppconn/statement.h \
    cppconn/warning.h


FORMS    += widget.ui

unix|win32: LIBS += -lmysqlcppconn

unix|win32: LIBS += -lmysqlcppconn-static
