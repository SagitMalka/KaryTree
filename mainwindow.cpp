#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Example tree
    tree.add_root(10).add_sub_node(10, 5).add_sub_node(10, 15).add_sub_node(5, 3).add_sub_node(5, 7);
    tree.myHeap();
    // tree.insert(10);
    // tree.insert(5);
    // tree.insert(15);
    // tree.insert(3);
    // tree.insert(7);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    int dx = width() / 4;  // Horizontal distance between nodes
    int dy = 50;           // Vertical distance between nodes
    drawNode(painter, tree.getRoot(), width() / 2, 50, dx, dy);
}

void MainWindow::drawNode(QPainter &painter, std::shared_ptr<ariel::Node<int>> node, int x, int y, int dx, int dy) {
    if (!node) return;

    painter.drawEllipse(x - 15, y - 15, 30, 30);
    painter.drawText(x - 10, y + 5, QString::number(node->_val));

    if (node->_left_most) {
        painter.drawLine(x, y, x - dx, y + dy);
        drawNode(painter, node->_left_most, x - dx, y + dy, dx / 2, dy);
    }

    if (node->_right_most) {
        painter.drawLine(x, y, x + dx, y + dy);
        drawNode(painter, node->_right_most, x + dx, y + dy, dx / 2, dy);
    }
}
