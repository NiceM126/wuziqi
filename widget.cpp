#include "widget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QPushButton>
#include <QDateTime>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1200, 1200);//设置窗口大小

    QPushButton *button1 = new QPushButton(this);
    QPushButton *button2 = new QPushButton("点我退出游戏", this);

    button1->move(1000, 100);
    button1->setFixedSize(160, 80);
    button1->setText(QDateTime().currentDateTime().toString("yyyy/MM/dd"));

    button2->move(1000, 400);
    button2->setFixedSize(160, 80);

    connect(button2, &QPushButton::clicked, [ = ]() {
                this->close();
            });

    //dropchess.reserve(200);
    isBlueTurn = true;//蓝方先下

}

void Widget::paintEvent(QPaintEvent *)
{
    drawChessBoard();
    drawChess();
    drawChessWithMouse();
    update();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    QPoint pt;
    int x = e->x();
    int y = e->y();
    if(x / 80 < 1 || x / 80 > 12 || y / 80 < 1 || y / 80 > 12) {
        return;
    }
    if (x % 80 <= 40) {
        pt.setX( x / 80 - 1);
    } else {
        pt.setX( x / 80);
    }

    if (y % 80 <= 40)

    {
        pt.setY( y / 80 - 1);
    } else {
        pt.setY( y / 80);
    }

    qDebug() << "x =" << x << ", " << "x % 80 =" << x % 80 << ", pt.x=" << pt.x();
    qDebug() << "y =" << y << ", " << "y % 80 =" << x % 80 << ", pt.y=" << pt.y();

    for(int i = 0; i < dropchess.size(); i++) {
        Chess chess = dropchess[i];
        if (chess.ChessPos == pt) {
            return;
        }

    }

    Chess chess1(pt, isBlueTurn);
    dropchess.append(chess1);

    //统计四个方向是否有5个相同颜色的棋子
    int nLeft = CountNearChess(chess1, QPoint(-1, 0));
    int nLeftUp = CountNearChess(chess1, QPoint(-1, -1));
    int nUp = CountNearChess(chess1, QPoint(0, -1));
    int nRightUp = CountNearChess(chess1, QPoint(1, -1));
    int nRight = CountNearChess(chess1, QPoint(1, 0));
    int nRightDown = CountNearChess(chess1, QPoint(1, 1));
    int nDown = CountNearChess(chess1, QPoint(0, 1));
    int nLeftDown = CountNearChess(chess1, QPoint(-1, 1));
    if ( (nLeft + nRight) >= 4 ||
            (nLeftUp + nRightDown) >= 4 ||
            (nUp + nDown) >= 4 ||
            (nRightUp + nLeftDown) >= 4 ) {

        QString str;
        if(isBlueTurn) {

            str = "蓝方胜出";
        } else {

            str = "红方胜出";
        }

        QMessageBox::information(NULL,  "游戏结束", str, QMessageBox::Yes, QMessageBox::Yes);
        dropchess.clear();
        //NewGame();
        return;
    }
    isBlueTurn = !isBlueTurn;//换另一方下棋
}

void Widget::drawChessBoard()
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.setPen(QPen(QColor(Qt::black), 2));

    //12x12棋盘
    for(int i = 0; i <= 960; i += 80) {
        painter.drawLine(i, 0, i, 960);
    }
    for (int j = 0; j <= 960; j += 80) {
        painter.drawLine(0, j, 960, j);
    }
}

void Widget::drawChess()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    for(int i = 0; i < dropchess.size(); i++ ) {
        Chess chess = dropchess[i];
        QPoint pt((chess.ChessPos.x() + 1) * 80, (chess.ChessPos.y()  + 1) * 80);
        if(chess.ChessColor) {
            painter.setBrush(Qt::blue);

        } else {
            painter.setBrush(Qt::red);
        }
        drawChessAtPoint(painter, pt);
    }
}

void Widget::drawChessWithMouse()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    if(isBlueTurn) {
        painter.setBrush(Qt::blue);
    } else {
        painter.setBrush(Qt::red);
    }

    QPoint point;
    if(!(point.x() / 80 < 1 || point.x() / 80 > 12 || point.y() / 80 < 1 || point.y() / 80 > 12)) {
        painter.drawEllipse(point, 40, 40);
    }
}

void Widget::drawChessAtPoint(QPainter &painter, QPoint &pt)
{
    painter.drawEllipse(pt, 40, 40);
}

int Widget::CountNearChess(Chess chess, QPoint ptd)
{
    int count = 0;//记录相连棋子数
    Chess it = chess;
    it.ChessPos += ptd;
    while(dropchess.contains(it)) {
        count++;
        it.ChessPos += ptd;
    }
    return count;
}

Widget::~Widget()
{
}


