#include "Readyboard.h"

ReadyBoard::ReadyBoard(QObject *parent) :
    GameElement(parent)
{
    this->addFrame(QPixmap(":/image/image/text_ready.png"));
    this->addFrame(QPixmap(":/image/image/tutorial.png"));
    this->init();
}

void ReadyBoard::init()
{
}

void ReadyBoard::logic()
{
    if(!this->enabledLogic)
        return;
}

void ReadyBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    painter->drawPixmap(45.0,145.0,197.0,63.0, this->pixmapList[0]);
    painter->drawPixmap(86.5,220.0,115.0,99.0,this->pixmapList[1]);
}
