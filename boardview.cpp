#include "boardview.h"
#include <iostream>

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
//    this->setUpdatesEnabled(false);
    this->setMouseTracking(true);
    grid_drawed = false;
    nodes = NULL;
    humanActive = 0;
}

BoardWidget::~BoardWidget()
{
    std::cout << "BoardWidget deleted" << std::endl;
}

void BoardWidget::paint()
{
    std::cout << "in paint" << std::endl;
//    this->setUpdatesEnabled(true);
    this->update();
}

void BoardWidget::paintEvent(QPaintEvent *)
{
    std::cout << "in paintevent: " << grid_drawed << std::endl;


    QWidget *parent = dynamic_cast<QWidget*>(this->parent());
    std::cout << parent->geometry().height() << std::endl;
    std::cout << parent->geometry().width() << std::endl;

    grid_up_left.setX(40);
    grid_up_left.setY(40);
    grid_half_len = 30;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //    painter.drawRect(0, 0, 400, 400);
    QPointF q;
    QPointF vx(2*grid_half_len, 0);
    QPointF vy(0, 2*grid_half_len);
    int i, j;
    for ( i = 0; i < this->width; i++ ) {
        q = grid_up_left + i * vx;
        for ( j = 0; j < this->height; j++ ) {
            painter.drawRect(q.x()-grid_half_len, q.y()-grid_half_len, 2*grid_half_len, 2*grid_half_len);
            q = q + vy;
        }
    }

    if ( nodes != NULL ) {
        for ( i = 0; i < this->width; i++ ) {
            for ( j = 0; j < this->height; j++ ) {
                //std::cout << this->nodes[j][i].getColor() << " " << std::flush;
                if ( this->nodes[j][i].getColor() == black ) {
                    painter.setBrush(Qt::black);
                    painter.setPen(Qt::black);
                    painter.drawEllipse(grid_up_left+QPointF(i*2*grid_half_len, j*2*grid_half_len), grid_half_len*0.9, grid_half_len*0.9);
                }
                else if ( this->nodes[j][i].getColor() == white ) {
                    painter.setBrush(Qt::white);
                    painter.setPen(Qt::white);
                    painter.drawEllipse(grid_up_left+QPointF(i*2*grid_half_len, j*2*grid_half_len), grid_half_len*0.9, grid_half_len*0.9);
                }
                else if ( this->nodes[j][i].availability == 1 ) {
                    painter.setPen(Qt::blue);
                    painter.setBrush(Qt::NoBrush);
                    painter.drawEllipse(grid_up_left+QPointF(i*2*grid_half_len, j*2*grid_half_len), grid_half_len*0.9, grid_half_len*0.9);
                }
            }
            //std::cout << std::endl;
        }
    }
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *e)
{
    std::cout << "mouse release" << std::endl;
    //QPoint init(grid_half_len, grid_half_len);
    QPointF rel =  e->pos() - grid_up_left;// + init;
    //std::cout << grid_up_left.x() << ", " << grid_up_left.y() << std::endl;
    //std::cout << e->pos().x() << ", " <<  e->pos().y() << std::endl;
    //std::cout << rel.x() << ", " <<  rel.y() << std::endl;
    int x = (rel.x()+grid_half_len) / (2*grid_half_len);
    int y = (rel.y()+grid_half_len) / (2*grid_half_len);
    std::cout << "(" << x << ", " << y << ")" << std::endl;
    if ( x >= 0 && y >= 0 && x < this->width && y < this->height && humanActive) {
        emit reqPos(x, y);
    }
}

void BoardWidget::mouseMoveEvent(QMouseEvent *)
{
   // std::cout << "mouse moving" << std::endl;
}

/*
vim: set et:
*/
