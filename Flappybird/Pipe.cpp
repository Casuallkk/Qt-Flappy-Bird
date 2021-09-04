#include "Pipe.h"
#include <iostream>
using namespace std;

Pipe::Pipe(int pos ,QObject *parent) :
    GameElement(parent)
{
    this->startPosition = pos;
    this->loadFrame();
    this->init();
}

void Pipe::init()//初始化水管
{
    this->currentFrame = 0;
    this->pipePassEmited = false;//未通过水管
    this->pipeRect[above].setRect(576 + this->startPosition*175.6,  -271.0 + rand()%200,   52.0,   321.0);
    this->pipeRect[following].setRect(576 + this->startPosition*175.6,  this->pipeRect[above].bottom() + 100.0,     52.0,   321.0);
    this->speedX = 2.5;
}

void Pipe::logic()
{
    if(!this->enabledLogic)
        return;

    this->pipeRect[above].translate(-this->speedX,0);//前一个水管前进
    this->pipeRect[following].translate(-this->speedX,0);//后一个水管也前进

    if(this->pipeRect[above].right() < 0)
    {
        this->pipeRect[above].moveTo(474.0,-271.0 + rand()%200);
        this->pipeRect[following].moveTo(474.0,this->pipeRect[above].bottom() + 100.0);
        this->pipePassEmited = false;
    }

    if(this->pipeRect[above].left() < 72 && this->pipePassEmited == false)
    {
        emit pipePass();//发送信号
        this->pipePassEmited = true;//通过水管
    }
}

void Pipe::draw(QPainter *painter)
{
    painter->drawPixmap(this->pipeRect[above].x(),this->pipeRect[above].y(),this->pipeRect[above].width(), this->pipeRect[above].height(),this->pixmapList[0]);
    painter->drawPixmap(this->pipeRect[following].x(),this->pipeRect[following].y(),this->pipeRect[following].width(),this->pipeRect[following].height(),this->pixmapList[1]);
}

void Pipe::loadFrame()
{
    if(rand()%2)
    {
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/pipe_down.png"));
        this->addFrame(QPixmap(":/image/image/pipe_up.png"));
    }
    else
    {
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/pipe3_down.png"));
        this->addFrame(QPixmap(":/image/image/pipe3_up.png"));
    }
}

QRectF& Pipe::getRect(PipeType type)
{
    return this->pipeRect[type];
}
