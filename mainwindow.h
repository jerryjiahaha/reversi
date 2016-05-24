#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(QWidget *parent = 0);
    ~BoardWidget();
    void paint();
protected:
    void paintEvent(QPaintEvent *event);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BoardWidget *board;
};
#endif // MAINWINDOW_H
