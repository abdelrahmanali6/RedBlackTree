#include "mainwindow.h"
#include "RedBlackTree.h"
#include "Node.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
