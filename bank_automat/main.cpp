#include "mainwindow.h"
#include "withdrawal.h"
#include "paaikkuna.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    paaikkuna w;
    w.show();
    return a.exec();
}
