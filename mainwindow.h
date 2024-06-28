#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "tree.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    ariel::Tree<int> tree;

    void drawNode(QPainter &painter, std::shared_ptr<ariel::Node<int>> node, int x, int y, int dx, int dy);
};

#endif // MAINWINDOW_H
