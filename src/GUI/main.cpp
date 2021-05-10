#include "mainwindow.h"
#include <QTextCodec>

#include <QApplication>

int main(int argc, char *argv[])
{

     QTextCodec *cyrillicCodec = QTextCodec::codecForName("UTF8");
    // QTextCodec::setCodecForTr(cyrillicCodec);
     QTextCodec::setCodecForLocale(cyrillicCodec);
     //QTextCodec::setCodecForCStrings(cyrillicCodec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
