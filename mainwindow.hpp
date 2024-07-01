#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include "tree.hpp"
#include "Complex.hpp"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace ariel;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    ariel::Tree<Complex> tree;

    template<typename T>
    QString toQString(const T& value);

    template<>
    QString toQString<std::string>(const std::string& value);

    template<>
    QString toQString<char>(const char& value);

    template<>
    QString toQString<Complex>(const Complex& value);

    //void drawNode(QPainter &painter, std::shared_ptr<Node<Complex>> node, int x, int y, int dx, int dy);
    template <typename T, int k>
    void drawNode(QPainter &painter, std::shared_ptr<ariel::Node<T, k>> node, int x, int y, int dx, int dy);
};

#endif // MAINWINDOW_H
