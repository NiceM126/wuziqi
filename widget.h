#ifndef WIDGET_H
#define WIDGET_H
#include <QPainter>
#include "chess.h"
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *);//重写绘图事件
    virtual void mousePressEvent(QMouseEvent *e);//重写鼠标事件
    void drawChessBoard();//画出棋盘
    void drawChess();//画棋子
    void drawChessWithMouse();//鼠标点击位置将要下的棋子
    void drawChessAtPoint(QPainter &painter, QPoint &pt);//指定点pt画出棋子
    int CountNearChess(Chess chess, QPoint ptd);//统计某个方向同色棋子数
    ~Widget();
private:
    QVector<Chess> dropchess;//以下棋子坐标容器
    bool isBlueTurn;//该蓝方下棋

};
#endif // WIDGET_H
