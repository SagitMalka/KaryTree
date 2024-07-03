#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

protected:
    // template <typename T, int k>
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    Tree<Complex, 5> tree;

    template<typename T>
    QString toQString(const T& value);

    // template <typename T, int k>
    void drawNode(QPainter &painter, std::shared_ptr<Tree<Complex, 5>::Node>, int x, int y, int xOffset, int yOffset);
};

#endif // MAINWINDOW_H
