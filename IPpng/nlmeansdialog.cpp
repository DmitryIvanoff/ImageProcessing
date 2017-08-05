#include "nlmeansdialog.h"
#include "ui_nlmeansdialog.h"

NLmeansDialog::NLmeansDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NLmeansDialog)
{
    ui->setupUi(this);
}

NLmeansDialog::~NLmeansDialog()
{
    delete ui;
}

void NLmeansDialog::on_buttonBox_accepted()
{
  Win.setWidth(ui->lineEdit->text().toInt());
  Win.setHeight(ui->lineEdit_2->text().toInt());
  block.setWidth(ui->lineEdit_3->text().toInt());
  block.setHeight(ui->lineEdit_4->text().toInt());

}

int NLmeansDialog::getSig() const
{
    return sig;
}

void NLmeansDialog::setSig(int value)
{
    sig = value;
}

int NLmeansDialog::getH() const
{
    return h;
}

void NLmeansDialog::setH(int value)
{
    h = value;
}

QSize NLmeansDialog::getBlock() const
{
    return block;
}

void NLmeansDialog::setBlock(const QSize &value)
{
    block = value;
}

QSize NLmeansDialog::getWin() const
{
    return Win;
}

void NLmeansDialog::setWin(const QSize &value)
{
    Win = value;
}
