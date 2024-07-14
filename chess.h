#ifndef CHESS_H
#define CHESS_H
#include <QPoint>

class Chess
{
public:
    Chess() {};
    Chess(QPoint pt, bool ChessColor);//有参构造，位置和颜色

    bool operator==(const Chess &c1)const
    {
        return ((ChessPos == c1.ChessPos) && (ChessColor == c1.ChessColor));
    }
    ~Chess(void) {};
public:
    QPoint ChessPos;//棋子位置
    bool ChessColor;//棋子颜色
};

#endif // CHESS_H
