#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T00:29:53
#
#-------------------------------------------------

QT       += widgets gui xmlpatterns xml

greaterThan(QT_MAJOR_VERSION, 4): QT += core

TARGET = daoshi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    word.cpp \
    opendialog.cpp \
    lessonloader.cpp \
    helper.cpp

HEADERS  += mainwindow.h \
    word.h \
    opendialog.h \
    lessonloader.h \
    helper.h

FORMS    += mainwindow.ui \
    opendialog.ui

RESOURCES += \
    main.qrc
