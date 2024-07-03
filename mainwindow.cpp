#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <sstream>
#include <string>
using namespace ariel;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Example tree

    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3(6.0, 7.0);
    Complex c4(8.0, 5.0);
    tree.add_root(c1).add_sub_node(c1, c2).add_sub_node(c1, c3).add_sub_node(c1, c4);
    //tree.add_root(10).add_sub_node(10, 5).add_sub_node(10, 15).add_sub_node(5, 3).add_sub_node(5, 7);
    //tree.myHeap();
    // tree.insert(10);
    // tree.insert(5);
    // tree.insert(15);
    // tree.insert(3);
    // tree.insert(7);
}

MainWindow::~MainWindow() {
    delete ui;
}

template<typename T>
QString MainWindow::toQString(const T& value) {
    std::stringstream ss;
    ss << value;
    return QString::fromStdString(ss.str());
}

template<>
QString MainWindow::toQString<std::string>(const std::string& value) {
    return QString::fromStdString(value);
}

template<>
QString MainWindow::toQString<char>(const char& value) {
    return QString(QChar(value));
}

// template<>
// QString MainWindow::toQString<Complex>(const Complex& value) {
//     return QString::fromStdString(value.toString());
// }
template<>
QString MainWindow::toQString<Complex>(const Complex& value) {
    return QString("(%1, %2)").arg(value.re()).arg(value.im());
}
template <typename T, int k>
void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    int dx = width() / 4;  // Horizontal distance between nodes
    int dy = 50;           // Vertical distance between nodes
    drawNode(painter, tree.getRoot(), width() / 2, 50, dx, dy);
}
// template <typename T, int k>
// void MainWindow::drawNode(QPainter &painter, std::shared_ptr<Node> node, int x, int y, int dx, int dy) {
//     if (!node) return;
//     // Set pen color for the ellipse outline
//     QPen pen(Qt::black);
//     painter.setPen(pen);

//     // Set brush color for the ellipse fill
//     QBrush brush(Qt::yellow);
//     painter.setBrush(brush);

//     painter.drawEllipse(x - 15, y - 15, 45, 30);
//     painter.drawText(x - 10, y + 5, toQString(node->_val));

//     double angleStep = 180.0 / (k + 1);

//     for (int i = 0; i < k; ++i) {
//         if (node->_children[i]) {
//             // Calculate the position of the child node
//             double angle = (i + 1) * angleStep;
//             int childX = x + static_cast<int>(dx * cos(angle * M_PI / 180.0));
//             int childY = y + static_cast<int>(dy * sin(angle * M_PI / 180.0));

//             // Draw the line to the child node
//             painter.drawLine(x, y, childX, childY);
//             // Recursively draw the child node
//             drawNode(painter, node->_children[i], childX, childY, dx / 2, dy);
//         }
//     }
// }
void MainWindow::drawNode(QPainter &painter, std::shared_ptr<Tree<Complex, 3>::Node> node, int x, int y, int xOffset, int yOffset) {
    if (node == nullptr) {
        return;
    }

    painter.setBrush(Qt::yellow);
    painter.drawEllipse(x - 15, y - 15, 30, 30);

    painter.drawText(x - 10, y + 5, toQString(node->_val));

    int childXOffset = xOffset / 2;
    int childYOffset = yOffset + 50;

    for (size_t i = 0; i < node->_children.size(); ++i) {
        if (node->_children[i] != nullptr) {
            int childX = x + (i - 1) * xOffset;
            int childY = y + yOffset;

            painter.drawLine(x, y, childX, childY);
            drawNode(painter, node->_children[i], childX, childY, childXOffset, childYOffset);
        }
    }
}
