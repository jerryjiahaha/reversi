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

    board_view = new BoardWidget(this);
    board_view->setWidth(board_model->getWidth());
    board_view->setHeight(board_model->getHeight());

    board_view->setBackgroundRole(QPalette::Text);
    board_view->setAutoFillBackground(true);
    board_view->setMinimumSize(200, 200);
    board_view->setGeometry( 20, 50, 500, 500);

//    board_view->paint();
    this->on_actionNew_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board_view;
    delete board_model;
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
    std::cout << newgame->imfirstCheck->isChecked() << std::endl;
    this->board_model->init();
    this->board_view->setNodes(this->board_model->getNodes());
    connect(board_view, SIGNAL(reqPos(int,int)), this, SLOT(handleNextPos(int,int)));
    this->board_view->paint();
}

void MainWindow::handleNextPos(int x, int y)
{
    std::cout << "handleNextPos" << x << y << std::endl;
    if ( this->board_model->setNext(x, y) == 0 ) {
        this->board_view->paint();
    }
}

/*
vim: set et:
*/
