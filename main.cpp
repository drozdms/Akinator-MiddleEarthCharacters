#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <iostream>



int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    QFile File("QTDark.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    a.setStyleSheet(styleSheet);
    MainWindow w;
    w.show();
    a.exec();
    return 0;
}
