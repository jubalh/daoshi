#include <QApplication>
#include <QCommandLineParser>
#include "mainwindow.h"
#include "version.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName(NAME);
    a.setApplicationVersion(VERSION);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    MainWindow w;
    w.show();

    return a.exec();
}
