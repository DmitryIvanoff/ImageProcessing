#ifndef BINDIALOG_H
#define BINDIALOG_H

#include <QDialog>

namespace Ui {
class BinDialog;
}

class BinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BinDialog(QWidget *parent = 0);
    ~BinDialog();
    void SetSigma(unsigned char w)
    {
        T=w;
    }
    unsigned char GetSigma()
    {
        return T;
    }

private slots:
    void on_buttonBox_accepted();

signals:
    void closed();
private:
    unsigned char T;
    Ui::BinDialog *ui;
};

#endif // BINDIALOG_H
