#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QSettings>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.show();



    return a.exec();
}