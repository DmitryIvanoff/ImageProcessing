#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    width=height=0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();
    width=str1.toInt();
    height=str2.toInt();
    emit closed();
}

