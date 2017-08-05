#include "noizedialog.h"
#include "ui_noizedialog.h"

NoizeDialog::NoizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoizeDialog)
{
    ui->setupUi(this);
}

NoizeDialog::~NoizeDialog()
{
    delete ui;
}

void NoizeDialog::on_buttonBox_accepted()
{
    QString str1=ui->lineEdit->text();
    sigma=str1.toDouble();
    emit closed();

}
