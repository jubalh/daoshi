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
    lessonloader.cpp \
    helper.cpp \
    lesson.cpp \
    checkonline.cpp \
    openlessondialog.cpp \
    downloadlessondialog.cpp

HEADERS  += mainwindow.h \
    word.h \
    lessonloader.h \
    helper.h \
    lesson.h \
    version.h \
    checkonline.h \
    openlessondialog.h \
    downloadlessondialog.h

FORMS    += mainwindow.ui \
    opendialog.ui \
    downloadlessondialog.ui

RESOURCES += \
    main.qrc
