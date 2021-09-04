#ifndef ELEBACKGROUND_H
#define ELEBACKGROUND_H
//背景
#include "GameElement.h"

class Background : public GameElement
{
    Q_OBJECT
private:
    int currentFrame;
    void loadFrame();
public:
    explicit Background(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
};

#endif // ELEBACKGROUND_H
