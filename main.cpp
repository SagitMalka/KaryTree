#include "mainwindow.hpp"
#include <iostream>
#include <QApplication>
#include <tree.hpp>
using namespace ariel;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::cout << w.tree << std::endl;
    MainWindow w2;
    w2.tree.myHeap();
    w2.show();
    return a.exec();
}
