#include "mainwindow.h"
#include <QApplication>

#include "PngProc.h"
#include <string.h>
#include <stdio.h>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/Icons/icons/icon3.png"));
    w.show();

    return a.exec();
}
