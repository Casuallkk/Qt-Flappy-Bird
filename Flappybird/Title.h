#ifndef TITLE_H
#define TITLE_H

#include <QTimer>
#include"GameElement.h"
//初始界面小鸟和标题的实现
class Title : public GameElement
{
    Q_OBJECT
private:
    QTimer timer;//计时器，通过计时器实现小鸟的“飞行”
    int lastFrame;
    int currentFrame;
    void loadFrame();

public:
    explicit Title(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

signals:

public slots:
    void updateFrame();

};

#endif // TITLE_H
