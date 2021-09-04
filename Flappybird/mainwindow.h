#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QPixmap>
#include <QSound>
#include <QDesktopWidget>
#include<QBitmap>


#include "Background.h"
#include "Ground.h"
#include "Bird.h"
#include "Pipe.h"
#include "Scoreboard.h"
#include "Readyboard.h"
#include "Overboard.h"
#include "Title.h"
#include"dialog.h"

//四种游戏状态
enum GameStatus{GAMETITLE,GAMEREADY,GAMEPLAY,GAMEOVER};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QPixmap *bufferPixmap;

    //界面上的按钮
    QPushButton *startButton;
    QPushButton *closeButton;
    QPushButton *infoButton;

    //需要在界面上绘制的游戏元素
    Background *background;
    Ground *ground;
    Bird *bird;
    Pipe *pipe[3];
    ScoreBoard *scoreboard;
    ReadyBoard *readyboard;
    OverBoard *overboard;
    Title *title;

    //音效
    QSound *soundDie;
    QSound *soundHit;
    QSound *soundPoint;
    QSound *soundSwooshing;
    QSound *soundWing;

    int score; //分数
    QRectF impactBirdRect; //测试小鸟的影响
    GameStatus status;//游戏状态
    QTimer timer; //主计时器，刷新交互

    //对应的四种状态函数/
    void gameTitle();
    void gameReady();
    void gamePlay();
    void gameOver();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //重载paintEvent,mouseEvent,resizeEvent函数
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
public slots:
    void getScore();
    void startGame();
    void closeGame();
    void displayInfo();
    void setButtonVisible(bool,bool,bool);
};

#endif // MAINWINDOW_H
