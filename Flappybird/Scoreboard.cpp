#include "Scoreboard.h"

ScoreBoard::ScoreBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void ScoreBoard::init()
{
    this->bindRect.setRect(131.5,80.0,25.0,45.0);
    this->score = 0;

    this->tempUnit = 0;
    this->tempDecade = 0;
    this->tempHundred = 0;
}

void ScoreBoard::logic()
{
    if(!this->enabledLogic)
    {
        return;
    }
    else
    {
        this->tempUnit = this->score%10;
        this->tempDecade = (this->score%100)/10;
        this->tempHundred = (this->score%1000)/100;
    }
}

void ScoreBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
    {
        return;
    }
    else
    {
        //只画个位
        if(this->tempDecade == 0 && this->tempHundred == 0)
        {
            painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(), this->bindRect.height(),this->pixmapList[this->tempUnit]);
        }
        //只画个位和十位
        else if(this->tempHundred == 0)
        {
            painter->drawPixmap(this->bindRect.x()-10.0,this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[this->tempDecade]);
            painter->drawPixmap(this->bindRect.x()+10.0,this->bindRect.y(),this->bindRect.width(),this->bindRect.height(), this->pixmapList[this->tempUnit]);
        }
        else
        {
            //都画
            painter->drawPixmap(this->bindRect.x()-20.0, this->bindRect.y(),this->bindRect.width(), this->bindRect.height(),this->pixmapList[this->tempHundred]);
            painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[this->tempDecade]);
            painter->drawPixmap(this->bindRect.x()+19.0,this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[this->tempUnit]);
        }
    }
}

void ScoreBoard::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/font_048.png"));//ps:这其实是个“0”...虽然在游戏中看起来挺像个“1”的...
    this->addFrame(QPixmap(":/image/image/font_049.png"));
    this->addFrame(QPixmap(":/image/image/font_050.png"));
    this->addFrame(QPixmap(":/image/image/font_051.png"));
    this->addFrame(QPixmap(":/image/image/font_052.png"));
    this->addFrame(QPixmap(":/image/image/font_053.png"));
    this->addFrame(QPixmap(":/image/image/font_054.png"));
    this->addFrame(QPixmap(":/image/image/font_055.png"));
    this->addFrame(QPixmap(":/image/image/font_056.png"));
    this->addFrame(QPixmap(":/image/image/font_057.png"));
}

void ScoreBoard::setScore(int sc)
{
    this->score = sc;
}
