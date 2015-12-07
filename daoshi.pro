#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T00:29:53
#
#-------------------------------------------------

QT       += widgets gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core

TARGET = daoshi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    word.cpp \
    opendialog.cpp

HEADERS  += mainwindow.h \
    word.h \
    opendialog.h

FORMS    += mainwindow.ui \
    opendialog.ui

RESOURCES += \
    main.qrc
