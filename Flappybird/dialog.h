#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QPushButton>
#include<QDebug>
#include<QLabel>
#include<QPainter>
#include<QBitmap>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
     Ui::Dialog *ui;
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void on_okbutton_clicked();
};

#endif // DIALOG_H
