#ifndef ELEREADYBOARD_H
#define ELEREADYBOARD_H
//准备界面
#include "GameElement.h"

class ReadyBoard : public GameElement
{
    Q_OBJECT
public:
    explicit ReadyBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:

public slots:

};

#endif // ELEREADYBOARD_H
