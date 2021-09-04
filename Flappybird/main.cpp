#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //带图片的加载页
    QPixmap pixmap(":/image/image/loading.png");
    QSplashScreen splash(pixmap);
    splash.show();
    for(int i=0;i<50000000;i++);
    MainWindow w;
    splash.finish(&w);
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);//居中显示窗口
    splash.finish(&w);
    return a.exec();
}
