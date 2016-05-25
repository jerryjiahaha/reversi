#ifndef BOARD_VIEW_H_
#define BOARD_VIEW_H_

#include <QWidget>
#include <QPainter>
#include <QPoint>

#include "virtual_board.h"

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(QWidget *parent = 0);
    ~BoardWidget();
    void setWidth(int _width) { width = _width; }
    void setHeight(int _height) { height = _height; }
    void setNodes(const vBoardNode **_n) { nodes = _n; }
    void paint();
signals:
    void reqPos(int, int);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    int width;
    int height;
    QPoint grid_up_left;
    int grid_half_len;
    bool grid_drawed;
    const vBoardNode **nodes;
};


#endif

/*
vim: set et:
*/
