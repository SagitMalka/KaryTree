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
    template <typename T, int k>
    void paintEvent(QPaintEvent *event) ;

private:
    Ui::MainWindow *ui;
    Tree<Complex, 3> tree;

    template<typename T>
    QString toQString(const T& value);

    template<>
    QString toQString<string>(const string& value);

    template<>
    QString toQString<char>(const char& value);

    template<>
    QString toQString<Complex>(const Complex& value);

     void drawNode(QPainter &painter, std::shared_ptr<Tree<Complex, 3>::Node> node, int x, int y, int xOffset, int yOffset);
    //void drawNode(QPainter &painter, std::shared_ptr<Node<Complex>> node, int x, int y, int dx, int dy);
    // template <>
    // void drawNode(QPainter &painter, const std::shared_ptr<Node> node, int x, int y, int dx, int dy);
};

#endif // MAINWINDOW_H
