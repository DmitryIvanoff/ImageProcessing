#include "impulsenoizedialog.h"
#include "ui_impulsenoizedialog.h"

ImpulseNoizeDialog::ImpulseNoizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImpulseNoizeDialog)
{
    ui->setupUi(this);
}

ImpulseNoizeDialog::~ImpulseNoizeDialog()
{
    delete ui;
}

void ImpulseNoizeDialog::on_buttonBox_accepted()
{
    QString str=QString();
    str=ui->lineEdit_3->text();
    p[0]=str.toDouble();
    str=ui->lineEdit_4->text();
    p[1]=str.toDouble();
    str=ui->lineEdit_2->text();
    z[0]=str.toDouble();
    str=ui->lineEdit->text();
    z[1]=str.toDouble();
    emit closed();
}

double ImpulseNoizeDialog::getP(unsigned char ind) const
{
    if (ind<2)
    {
       return p[ind];
    }
    else
    {
        return 0.0;
    }
}

void ImpulseNoizeDialog::setP(double p_a, double p_b)
{
    p[0]=p_a;
    p[1]=p_b;
}

double ImpulseNoizeDialog::getz(unsigned char ind) const
{
    if (ind<2)
    {
       return z[ind];
    }
    else
    {
        return 0.0;
    }
}

void ImpulseNoizeDialog::setz(double a, double b)
{
    z[0]=a;
    z[1]=b;
}
