#include "addnoizedialog.h"
#include "ui_addnoizedialog.h"

AddNoizeDialog::AddNoizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNoizeDialog)
{
    ui->setupUi(this);
}

AddNoizeDialog::~AddNoizeDialog()
{
    delete ui;
}

void AddNoizeDialog::on_buttonBox_accepted()
{
    QString str1=ui->lineEdit->text();
    sigma=str1.toDouble();
    emit closed();
}
