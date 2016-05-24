#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board = new BoardWidget(this);
    board->setBackgroundRole(QPalette::Text);
    board->setAutoFillBackground(true);
    board->setMinimumSize(100, 100);
    board->setGeometry( 10, 30, 500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
}

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
}

BoardWidget::~BoardWidget()
{
}

void BoardWidget::paint()
{
    this->paintEvent(NULL);
}

void BoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawRect(0, 0, 500, 500);
}
