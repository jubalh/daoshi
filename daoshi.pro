#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T00:29:53
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5) {
  error("Requires at least Qt 5.4.")
} else {
  if(equals(QT_MAJOR_VERSION, 5)){
    lessThan(QT_MINOR_VERSION, 4): error("Requires at least Qt 5.4")
  }
}

QT       += widgets gui xmlpatterns xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += core

TARGET = daoshi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    word.cpp \
    opendialog.cpp \
    lessonloader.cpp \
    helper.cpp \
    lesson.cpp

HEADERS  += mainwindow.h \
    word.h \
    opendialog.h \
    lessonloader.h \
    helper.h \
    lesson.h \
    version.h

FORMS    += mainwindow.ui \
    opendialog.ui

RESOURCES += \
    main.qrc
