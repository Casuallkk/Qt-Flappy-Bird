#ifndef ELEGROUND_H
#define ELEGROUND_H
//地面
#include "GameElement.h"

class Ground : public GameElement
{
    Q_OBJECT
private:
    int currentFrame;
    int positionX;
    float speedX;//路的水平速度
public:
    explicit Ground(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
};

#endif // ELEGROUND_H
