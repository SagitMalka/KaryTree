#include <ui_mainwindow.h>

#include "mainwindow.hpp"
#include <sstream>


using namespace ariel;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Example tree

    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3(6.0, 7.0);
    Complex c4(8.0, 5.0);
    Complex c5(9.0, 5.0);
    Complex c6(6.0, 6.0);
    tree.add_root(c1).add_sub_node(c1, c2).add_sub_node(c1, c3);
    tree.add_sub_node(c2, c4).add_sub_node(c2, c5).add_sub_node(c3, c6);
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
    std::ostringstream oss;
    oss << value;
    return QString::fromStdString(oss.str());
}

// Specialization for Complex
template<>
QString MainWindow::toQString(const Complex& value) {
    return QString::fromStdString(value.toString());
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    int xOffset = width() / (2*tree.getKSize());
    int yOffset = 50;

    if (tree.getRoot() != nullptr) {
        drawNode(painter, tree.getRoot(), width() / 2, yOffset, xOffset, yOffset);
    }
}
// template <typename T, int k>
void MainWindow::drawNode(QPainter &painter, std::shared_ptr<Tree<Complex, 5>::Node>node, int x, int y, int xOffset, int yOffset) {
    if (node == nullptr) {
        return;
    }

    painter.setBrush(Qt::yellow);
    painter.drawEllipse(x - 15, y - 15, 45, 30);

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

