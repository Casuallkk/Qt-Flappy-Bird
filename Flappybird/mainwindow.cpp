#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setWindowFlag(Qt::FramelessWindowHint);//创建无边框窗口

    this->bufferPixmap = new QPixmap(288,512);//创建缓冲区防止闪烁
    this->resize(540,960); // 设置窗口大小

    //创建按钮，设置按钮样式，并连接槽与信号
    this->startButton = new QPushButton(this);
    this->startButton->setGeometry(QRect((20.0/288)*this->width(),
                                                         (341.0/512)*this->height(),
                                                         (117.0/288)*this->width(),
                                                         (71.0/512)*this->height()));
    this->startButton->setStyleSheet("QPushButton{border-image:url(:/image/image/button_play.png);}"
                                                           "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame()));

    this->closeButton = new QPushButton(this);
    this->closeButton->setGeometry(QRect((151.0/288)*this->width(),
                                                          (341.0/512)*this->height(),(117.0/288)*this->width(),
                                                          (71.0/512)*this->height()));
    this->closeButton->setStyleSheet("QPushButton{border-image:url(:/image/image/button_close.png);}"
                                                             "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));

    this->infoButton = new QPushButton(this);
    this->infoButton->setGeometry(QRect((106.5/288)*this->width(),(300.0/512)*this->height(),
                                                         (75.0/288)*this->width(), (48.0/512)*this->height()));
    this->infoButton->setStyleSheet("QPushButton{border-image:url(:/image/image/button_rate.png);}"
                                                           "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->infoButton,SIGNAL(clicked()),this,SLOT(displayInfo()));

    //初始化所有元素
    this->background = new Background();
    this->ground = new Ground();
    this->bird = new Bird();
    this->scoreboard = new ScoreBoard();
    this->readyboard = new ReadyBoard();
    this->overboard = new OverBoard();
    this->title = new Title();
    this->pipe[0] = new Pipe(0);
    this->pipe[1] = new Pipe(1);
    this->pipe[2] = new Pipe(2);

    this->impactBirdRect.setRect(0,0,0.4*this->bird->getBindRect().width(),0.4*this->bird->getBindRect().height());

    //音效
    this->soundDie = new QSound(":/sounds/sounds/sfx_die.wav");
    this->soundHit = new QSound(":/sounds/sounds/sfx_hit.wav");
    this->soundPoint = new QSound(":/sounds/sounds/sfx_point.wav");
    this->soundSwooshing = new QSound(":/sounds/sounds/sfx_swooshing.wav");
    this->soundWing = new QSound(":/sounds/sounds/sfx_wing.wav");

    //设置刷新率
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(20);

   //将槽函数与信号相连
    connect(this->pipe[0],SIGNAL(pipePass()),this,SLOT(getScore()));
    connect(this->pipe[1],SIGNAL(pipePass()),this,SLOT(getScore()));
    connect(this->pipe[2],SIGNAL(pipePass()),this,SLOT(getScore()));

    connect(this->overboard,SIGNAL(buttonVisible(bool,bool,bool)),this,SLOT(setButtonVisible(bool,bool,bool)));

    //游戏开始
    this->gameTitle();
}

MainWindow::~MainWindow()
{
    delete this->startButton;
    delete this->infoButton;
    delete this->closeButton;

    delete this->background;
    delete this->ground;
    delete this->bird;
    delete this->scoreboard;
    delete this->readyboard;
    delete this->overboard;
    delete this->title;
    delete this->pipe[0];
    delete this->pipe[1];
    delete this->pipe[2];
}

void MainWindow::mousePressEvent(QMouseEvent *event)//实现鼠标控制小鸟运动
{
    //游戏开始时，小鸟上升
    if( this->status == GAMEPLAY && event->button() == Qt::LeftButton )
    {
        this->soundWing->stop();
        this->bird->birdUp();
        this->soundWing->play();
    }

    if( this->status == GAMEREADY && event->button() == Qt::LeftButton )
    {
        this->gamePlay();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this->bufferPixmap);
    //绘制所有元素
    this->background->logic();
    this->background->draw(&painter);

    this->pipe[0]->logic();
    this->pipe[0]->draw(&painter);

    this->pipe[1]->logic();
    this->pipe[1]->draw(&painter);

    this->pipe[2]->logic();
    this->pipe[2]->draw(&painter);

    this->bird->logic();
    this->bird->draw(&painter);

    this->scoreboard->logic();
    this->scoreboard->draw(&painter);

    this->readyboard->logic();
    this->readyboard->draw(&painter);

    this->title->logic();
    this->title->draw(&painter);

    this->ground->logic();
    this->ground->draw(&painter);

    this->overboard->logic();
    this->overboard->draw(&painter);

    QPainter mainWindowPainter(this);
    mainWindowPainter.drawPixmap(QRect(0,0,this->width(),this->height()),*this->bufferPixmap);

    if(this->status == GAMEPLAY)
    {
        //更新鸟的角度
        this->impactBirdRect.moveCenter(this->bird->getBindRect().center());

        //测试影响是否发生
        if(this->impactBirdRect.intersects(this->ground->getBindRect()))
        {
            this->soundHit->play();
            this->gameOver(); //游戏结束
        }
        if(this->impactBirdRect.intersects(this->pipe[0]->getRect(above))||this->impactBirdRect.intersects(this->pipe[0]->getRect(following))||this->impactBirdRect.intersects(this->pipe[1]->getRect(above))||this->impactBirdRect.intersects(this->pipe[1]->getRect(following))||this->impactBirdRect.intersects(this->pipe[2]->getRect(above))||this->impactBirdRect.intersects(this->pipe[2]->getRect(following)))
        {
            this->soundHit->play();
            this->soundDie->play();
            this->gameOver(); //游戏结束
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->startButton->setGeometry(QRect((20.0/288)*this->width(), (341.0/512)*this->height(),(117.0/288)*this->width(), (71.0/512)*this->height()));
    this->closeButton->setGeometry(QRect((151.0/288)*this->width(),(341.0/512)*this->height(), (117.0/288)*this->width(), (71.0/512)*this->height()));
    this->infoButton->setGeometry(QRect((106.5/288)*this->width(), (300.0/512)*this->height(), (75.0/288)*this->width(),(48.0/512)*this->height()));
}

void MainWindow::gameTitle()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->title->enabledLogic = true;
    this->title->enabledDraw = true;

    this->bird->enabledLogic = false;
    this->bird->enabledDraw = false;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->pipe[0]->enabledLogic = false;
    this->pipe[0]->enabledDraw = false;
    this->pipe[1]->enabledLogic = false;
    this->pipe[1]->enabledDraw = false;
    this->pipe[2]->enabledLogic = false;
    this->pipe[2]->enabledDraw = false;
    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->setButtonVisible(true,true,true);
    this->status = GAMETITLE;
}

void MainWindow::gameReady()
{
    this->score = 0;

    //按钮隐藏
    this->setButtonVisible(false,false,false);
    this->status = GAMEREADY;

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->title->enabledLogic = false;
    this->title->enabledDraw = false;

    this->bird->enabledLogic = false;
    this->bird->enabledDraw = true;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->pipe[0]->enabledLogic = false;
    this->pipe[0]->enabledDraw = false;
    this->pipe[1]->enabledLogic = false;
    this->pipe[1]->enabledDraw = false;
    this->pipe[2]->enabledLogic = false;
    this->pipe[2]->enabledDraw = false;

    this->readyboard->enabledLogic = true;
    this->readyboard->enabledDraw = true;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

}

void MainWindow::gamePlay()
{
     this->status = GAMEPLAY;
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->title->enabledLogic = false;
    this->title->enabledDraw = false;

    this->bird->enabledLogic = true;
    this->bird->enabledDraw = true;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->pipe[0]->enabledLogic = true;
    this->pipe[0]->enabledDraw = true;
    this->pipe[1]->enabledLogic = true;
    this->pipe[1]->enabledDraw = true;
    this->pipe[2]->enabledLogic = true;
    this->pipe[2]->enabledDraw = true;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

}

void MainWindow::gameOver()
{
    this->status = GAMEOVER;
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->title->enabledLogic = false;
    this->title->enabledDraw = false;

    this->bird->enabledLogic = true;
    this->bird->enabledDraw = true;

    this->ground->enabledLogic = false;
    this->ground->enabledDraw = true;

    this->overboard->setScore(this->score);
    this->overboard->enabledLogic = true;
    this->overboard->enabledDraw = true;

    this->pipe[0]->enabledLogic = false;
    this->pipe[0]->enabledDraw = true;
    this->pipe[1]->enabledLogic = false;
    this->pipe[1]->enabledDraw = true;
    this->pipe[2]->enabledLogic = false;
    this->pipe[2]->enabledDraw = true;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

}

void MainWindow::startGame()
{
   //初始化所有游戏元素
    this->background->init();
    this->ground->init();
    this->bird->init();
    this->scoreboard->init();
    this->readyboard->init();
    this->overboard->init();
    this->pipe[0]->init();
    this->pipe[1]->init();
    this->pipe[2]->init();

    //游戏开始
    this->gameReady();

    this->soundSwooshing->play();
}

void MainWindow::closeGame()
{
    this->soundSwooshing->play();
    this->close();
}

void MainWindow::getScore()
{
    this->score += 1;
    this->scoreboard->setScore(this->score);
    this->soundPoint->play();
}

void MainWindow::displayInfo()
{
    //创建一个模态对话框，便于美化
    Dialog *dialog=new Dialog();
    dialog->deleteLater();
    int temp=dialog->exec();
}

void MainWindow::setButtonVisible(bool _startBtn, bool _scoreBtn, bool _rateBtn)
{
    this->startButton->setVisible(_startBtn);
    this->closeButton->setVisible(_scoreBtn);
    this->infoButton->setVisible(_rateBtn);
}
