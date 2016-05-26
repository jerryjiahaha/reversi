#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(200, 200, 700, 700);

    board_model = new vBoard;
    ai = new SmartGecko;

    board_view = new BoardWidget(this);
    board_view->setWidth(board_model->getWidth());
    board_view->setHeight(board_model->getHeight());

    board_view->setBackgroundRole(QPalette::Text);
    board_view->setAutoFillBackground(true);
    board_view->setMinimumSize(200, 200);
    board_view->setGeometry( 20, 50, 500, 500);

    connect(this, SIGNAL(nextPlayer()), this, SLOT(handleNextPlayer()));
    connect(this, SIGNAL(endOfGame()), this, SLOT(handleEndOfGame()));

//    board_view->paint();
    this->on_actionNew_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board_view;
    delete board_model;
    delete ai;
}
void MainWindow::on_actionNew_triggered()
{
    std::cout << "new action triggered" << std::endl;
    newgame = new newGameDialog(this);
    newgame->setAttribute(Qt::WA_DeleteOnClose);
    connect(newgame, SIGNAL(finished(int)), this, SLOT(startGame(int)));
    newgame->show();
}

void MainWindow::startGame(int res)
{
    std::cout << "game start! " << res << std::endl;
    imfirst = newgame->imfirstCheck->isChecked();
    std::cout << imfirst << std::endl;
    // always `black` first
    if ( imfirst ) {
        this->playerList[black] = 0;
        this->playerList[white] = 1;
        this->playerNames[black] = "ME_black";
        this->playerNames[white] = "AI_white";
        //blackisAi = 0;
        //whiteisAi = 1;
    }
    else {
        this->playerList[black] = 1;
        this->playerList[white] = 0;
        this->playerNames[black] = "AI_black";
        this->playerNames[white] = "ME_white";
        //blackisAi = 1;
        //whiteisAi = 0;
    }
    this->board_model->init();
    this->board_view->setNodes(this->board_model->getNodes());
    connect(board_view, SIGNAL(reqPos(int,int)), this, SLOT(handleNextPos(int,int)));
    this->board_view->paint();
    //this->statusBar()->showMessage(QVariant(this->board_model->getNext()).toString());
    emit nextPlayer();
}

void MainWindow::handleNextPos(int x, int y)
{
    std::cout << "handleNextPos" << x << y << std::endl;
    if ( this->playerList[this->board_model->getNext()] ) {
        return;
    }
    if ( this->board_model->setNext(x, y) == 0 ) {
        this->board_view->paint();
    }
    emit nextPlayer();
}

void MainWindow::handleNextPlayer() {
    std::cout << "in handleNextPlayer" << std::endl;
    this->board_view->setHumanDisabled();
    int state = this->board_model->checkNext();
    this->statusBar()->showMessage(this->playerNames[this->board_model->getNext()]);
    if ( state == END_OF_GAME_ ) {
        std::cout << "END_OF_GAME_" << std::endl;
        emit endOfGame();
        return;
    }
    if ( state == SWITCH_USER_) {
        std::cout << "SWITCH_USER_" << std::endl;
        emit nextPlayer();
        return;
    }
    int nextColor = this->board_model->getNext();
    int x = 0, y = 0;
    if ( this->playerList[nextColor] ) {
        std::cout << "now its turn of AI" << std::endl;
        this->ai->nextStep(x, y, *(this->board_model));
        if ( this->board_model->setNext(x, y) == 0 ) {
            this->board_view->paint();
            std::cout << "AI finished, next" << std::endl;
            emit nextPlayer();
        }
    }
    else {
        this->board_view->setHumanActive();
    }
}

void MainWindow::handleEndOfGame() {
    int whiteC = this->board_model->getWhite();
    int blackC = this->board_model->getBlack();
    QString q;
    if ( imfirst ) {
        q += "User: black\n";
    }
    else {
        q += "User: white\n";
    }
    q += "white: " + QVariant(whiteC).toString() + "\n";
    q += "black: " + QVariant(blackC).toString();
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setText(q);
    msgBox->show();
}

/*
vim: set et:
*/
