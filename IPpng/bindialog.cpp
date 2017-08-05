#include "bindialog.h"
#include "ui_bindialog.h"

BinDialog::BinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinDialog)
{
    ui->setupUi(this);
}

BinDialog::~BinDialog()
{
    delete ui;
}

void BinDialog::on_buttonBox_accepted()
{
    QString str1=ui->lineEdit->text();
    T=str1.toInt();
    emit closed();
}
