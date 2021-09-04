#ifndef ELEPIPE_H
#define ELEPIPE_H
//水管
#include "GameElement.h"

enum PipeType{above=0,following=1};

class Pipe : public GameElement
{
    Q_OBJECT
private:
    int currentFrame;//现有框架数量
    double speedX;//水管的速度
    int startPosition;//水管的初始位置
    QRectF pipeRect[2];
    bool pipePassEmited;//判断是否通过水管

    void loadFrame();
public:
    explicit Pipe(int pos,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

    QRectF &getRect(PipeType);
signals:
    void pipePass();//与emit()相对的函数

};

#endif // ELEPIPE_H
