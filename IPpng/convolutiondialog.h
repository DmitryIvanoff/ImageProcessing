#ifndef CONVOLUTIONDIALOG_H
#define CONVOLUTIONDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

#define MEDFLTFLAG 0x01
#define LINFLTFLAG 0x00
namespace Ui {
class ConvolutionDialog;
}

class ConvolutionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConvolutionDialog(QWidget *parent = 0,size_t s=3);
    ~ConvolutionDialog();
    double getValue(int i,int j);
    void setValue(int i,int j,double val);
    void getValues();
    size_t getSize() const;
    void setSize(const size_t &value);
public slots:
    void on_MedianFilter_opened();
    void on_LinearFilter_opened();
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_buttonBox_accepted();

    void on_checkBox_stateChanged(int arg1);

signals:
    void closed(int);
private:
    int fltflag;
    double countSum();
    double sum;
    size_t size;
    Ui::ConvolutionDialog *ui;
};

#endif // CONVOLUTIONDIALOG_H
