#include "globcontrastdialog.h"
#include "ui_globcontrastdialog.h"

GlobContrastDialog::GlobContrastDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlobContrastDialog)
{
    ui->setupUi(this);
    HT=CT=0;

}

GlobContrastDialog::~GlobContrastDialog()
{
    delete ui;
}

void GlobContrastDialog::on_buttonBox_accepted()
{
    QString str=QString();
    str=ui->lineEdit->text();
    HT=str.toInt();
    CT=str.toInt();
    emit closed();
}

int GlobContrastDialog::getCT() const
{
    return CT;
}

void GlobContrastDialog::setCT(int value)
{
    CT = value;
}

int GlobContrastDialog::getHT() const
{
    return HT;
}

void GlobContrastDialog::setHT(int value)
{
    HT = value;
}
