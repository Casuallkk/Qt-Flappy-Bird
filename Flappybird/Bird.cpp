#include "Bird.h"

Bird::Bird(QObject *parent) :
    GameElement(parent)
{
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void Bird::init()
{
    this->loadFrame();
    this->lastFrame = 0;
    this->currentFrame = 1;
    this->angle = 0;
    this->speedX = 7.0;
    this->speedY = -7.2;
    this->increaseY = 0.43;
    this->bindRect.setRect(58,220.0,49.0,49.0);
    this->timer.start(150);
}

void Bird::logic()
{
    if( !this->enabledLogic )
    {
        return;
    }
            //角度
            this->angle = qAtan2(this->speedY,this->speedX)*180.0/3.14;//qAtan2（）可以返回一个点坐标tan值
            if(this->angle < -10)
                this->angle = -25;
            else if(this->angle > 60)
                this->angle = 90;

            //Y
            this->speedY += this->increaseY;
            if(this->speedY > 14.0)
            {
                this->speedY = 14.0;
                this->angle = 90;
            }
            this->bindRect.translate(0,this->speedY);//相当于当前位置，小鸟在x方向移动0，在y方向沿Y轴移动speedY

            //限制
            if(this->bindRect.top() < -this->bindRect.height())
                this->bindRect.moveTop(-this->bindRect.height());
            if(this->bindRect.bottom() > 415.0)
            {
                this->bindRect.moveBottom(415.0);
                this->timer.stop();
            }
            return;
}

void Bird::draw(QPainter *painter)
{
    if( !this->enabledDraw )
        return;
        painter->save();
        painter->translate(this->bindRect.center());
        painter->rotate(this->angle);
        painter->translate(-this->bindRect.center());
        painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[this->currentFrame]);
        painter->restore();
}

void Bird::loadFrame()
{
    switch(rand()%3)
    {
    case 0:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/bird0_0.png"));
        this->addFrame(QPixmap(":/image/image/bird0_1.png"));
        this->addFrame(QPixmap(":/image/image/bird0_2.png"));
        break;
    case 1:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/bird1_0.png"));
        this->addFrame(QPixmap(":/image/image/bird1_1.png"));
        this->addFrame(QPixmap(":/image/image/bird1_2.png"));
        break;
    case 2:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/bird2_0.png"));
        this->addFrame(QPixmap(":/image/image/bird2_1.png"));
        this->addFrame(QPixmap(":/image/image/bird2_2.png"));
        break;
    }
}

void Bird::birdUp()
{
    this->speedY = -8;//小鸟上升
}

void Bird::updateFrame()//更新框架
{
    if( !this->enabledDraw )
        return;

    if(this->currentFrame > this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame++;
    }
    else if(this->currentFrame < this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame--;
    }

    if(this->currentFrame<0 || this->currentFrame>2)
        this->currentFrame = 1;
}

