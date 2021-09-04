#ifndef ELESCOREBOARD_H
#define ELESCOREBOARD_H
//游戏中实时显示分数
#include "GameElement.h"

class ScoreBoard : public GameElement
{
    Q_OBJECT
private:
    int score;
    int tempUnit;//分数的个位
    int tempDecade;//分数的十位
    int tempHundred;//分数的百位（PS：我感觉我想多了根本没人能玩这么多分...分数能到两位数就已经很困难了....可能是我写太难了？也可能是我游戏技术太菜了...）
    void loadFrame();

public:
    explicit ScoreBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void setScore(int);

signals:

public slots:

};

#endif // ELESCOREBOARD_H
