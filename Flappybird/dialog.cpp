#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    QPalette pl = this->palette();
    this->setPalette(pl);
    this->setAutoFillBackground(true);
    setWindowTitle(QString("About"));
    connect(ui->okbutton,SIGNAL(clicked()),this,SLOT(on_okbutton_clicked()));
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_okbutton_clicked()
{
    accept();
}

