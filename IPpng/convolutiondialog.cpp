#include "convolutiondialog.h"
#include "ui_convolutiondialog.h"
#include <QDebug>
#include <QCheckBox>
ConvolutionDialog::ConvolutionDialog(QWidget *parent, size_t s) :
    QDialog(parent),
    ui(new Ui::ConvolutionDialog)
{
    ui->setupUi(this);
    size=s;
    ui->spinBox->setValue(s);
    ui->tableWidget->setColumnCount(s);
    ui->tableWidget->setRowCount(s);
    for (int i=0;i<size;++i)
    {
        for (int j=0;j<size;++j)
        {
            setValue(i,j,1.0);
        }
    }
    sum=1.0;
}

ConvolutionDialog::~ConvolutionDialog()
{
    delete ui;
}

double ConvolutionDialog::getValue(int i, int j)
{
    double r=0.0;
    QString str;
    if ((i<size)&&(j<size))
    {
       str=QString(ui->tableWidget->item(i,j)->text());
    }
    r=str.toDouble();
    return (r/sum);

}

void ConvolutionDialog::setValue(int i, int j, double val)
{
    QTableWidgetItem* itm=ui->tableWidget->takeItem(i,j);
    itm->setText(QString::number(val));
    ui->tableWidget->setItem(i,j,itm);
}

void ConvolutionDialog::getValues()
{

}

void ConvolutionDialog::on_spinBox_valueChanged(int arg1)
{
    size=arg1;
    ui->tableWidget->setColumnCount(arg1);
    ui->tableWidget->setRowCount(arg1);
}

void ConvolutionDialog::on_buttonBox_accepted()
{
    switch (fltflag)
    {
       case MEDFLTFLAG:
        break;
       case LINFLTFLAG:
        // sum=countSum();
        break;
    }
    closed(fltflag);
}

double ConvolutionDialog::countSum()
{
    double r;
    double s=0.0;
    QString str;
    for (int i=0;i<size;++i)
    {
        for(int j=0;j<size;++j)
        {
            if ((i<size)&&(j<size))
            {
               str=QString(ui->tableWidget->item(i,j)->text());
            }
            r=str.toDouble();
            s+=r;
        }
    }
    return s;
}

size_t ConvolutionDialog::getSize() const
{
    return size;
}

void ConvolutionDialog::setSize(const size_t &value)
{
    size = value;
}

void ConvolutionDialog::on_MedianFilter_opened()
{
    fltflag=MEDFLTFLAG;
    switch (ui->checkBox->checkState())
    {
      case Qt::Unchecked:
         sum=1.0;
         break;
      case Qt::Checked:
        sum=countSum();
        break;
    }
}

void ConvolutionDialog::on_LinearFilter_opened()
{
    fltflag=LINFLTFLAG;
    switch (ui->checkBox->checkState())
    {
      case Qt::Unchecked:
         sum=1.0;
         break;
      case Qt::Checked:
         sum=countSum();
        break;
    }
}



void ConvolutionDialog::on_checkBox_stateChanged(int state)
{
    switch (state)
    {
      case Qt::Unchecked:
         sum=1.0;
         break;
      case Qt::Checked:
        sum=countSum();
        break;
    }

}
