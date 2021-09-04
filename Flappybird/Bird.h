#ifndef BIRD_H
#define BIRD_H
//小鸟
#include "GameElement.h"

#include <QTimer>
#include <QtMath>


class Bird : public GameElement
{
    Q_OBJECT
private:
    int lastFrame;
    int currentFrame;
    float speedY;//竖直速度
    float increaseY;//每次鼠标点击上升的距离、上升速度
    float speedX;//水平速度
    int angle;//俯冲角度
    QTimer timer;//定时器
    void loadFrame();

public:
    explicit Bird(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void birdUp();//小鸟上升

signals:

public slots:
    void updateFrame();//更新现有框架
};

#endif // BIRD_H
