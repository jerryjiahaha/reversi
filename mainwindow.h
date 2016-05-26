#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QObject>
#include <QMessageBox>
//#include <QThread>
#include <map>

#include "virtual_board.h"
#include "boardview.h"
#include "newgamedialog.h"

#include "ai/SmartGecko.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void nextPlayer();
    void endOfGame();

private slots:
    void on_actionNew_triggered();
    void startGame(int ret);
    void handleNextPos(int x, int y);
    void handleNextPlayer();
    void handleEndOfGame();
    //void updateInfo();
private:
    Ui::MainWindow *ui;
    BoardWidget *board_view;
    vBoard *board_model;
    newGameDialog *newgame;
    int imfirst;
    std::map<int, int> playerList; // Ai:1, human:0
    std::map<int, QString> playerNames;
    SmartGecko *ai;
    //int whiteisAi;
    //int blackisAi;
};
#endif // MAINWINDOW_H
