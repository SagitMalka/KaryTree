
// sagitmalka10@gmail.com

#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include "tree.hpp"
#include "Complex.hpp"


using namespace ariel;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Tree<Complex, 2> tree;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;


    template<typename T>
    QString toQString(const T& value);
    void drawNode(QPainter &painter, std::shared_ptr<Tree<Complex, 2>::Node>, int x, int y, int xOffset, int yOffset);
};

