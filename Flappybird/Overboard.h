#ifndef ELEOVERBOARD_H
#define ELEOVERBOARD_H
//游戏结束界面
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "GameElement.h"

enum Medal{PLATINICMEDAL = 12,GOLDMEDAL = 13,SILVERMEDAL = 14,COPPERMEDAL = 15,NONE = 0};

class OverBoard : public GameElement
{
    Q_OBJECT
private:
    int score;
    int highestScore;
    Medal medal;
    bool scoreLabelArrived;
    QRectF scoreLabelRect;
    QRectF overTextRect;
    void loadFrame();
    int getHighestScore();
public:
    explicit OverBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void setScore(int);

signals:
    void buttonVisible(bool,bool,bool);
public slots:
};

#endif // ELEOVERBOARD_H
