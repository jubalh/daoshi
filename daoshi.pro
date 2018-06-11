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


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/word.cpp \
    src/lessonloader.cpp \
    src/helper.cpp \
    src/lesson.cpp \
    src/checkonline.cpp \
    src/openlessondialog.cpp \
    src/downloadlessondialog.cpp \
    src/availablelessonsmodel.cpp \
    src/onlinelesson.cpp

HEADERS  += src/mainwindow.h \
    src/word.h \
    src/lessonloader.h \
    src/helper.h \
    src/lesson.h \
    src/version.h \
    src/checkonline.h \
    src/openlessondialog.h \
    src/downloadlessondialog.h \
    src/availablelessonsmodel.h \
    src/onlinelesson.h

FORMS    += src/mainwindow.ui \
    src/opendialog.ui \
    src/downloadlessondialog.ui

RESOURCES += \
    main.qrc
