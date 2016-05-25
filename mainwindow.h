#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QObject>

#include "virtual_board.h"
#include "boardview.h"
#include "newgamedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void startGame(int ret);
	void handleNextPos(int x, int y);
private:
    Ui::MainWindow *ui;
    BoardWidget *board_view;
    vBoard *board_model;
    newGameDialog *newgame;
};
#endif // MAINWINDOW_H
