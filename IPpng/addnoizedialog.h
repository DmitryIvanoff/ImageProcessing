#ifndef ADDNOIZEDIALOG_H
#define ADDNOIZEDIALOG_H

#include <QDialog>

namespace Ui {
class AddNoizeDialog;
}

class AddNoizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNoizeDialog(QWidget *parent = 0);
    ~AddNoizeDialog();
    void SetSigma(double w)
    {
        sigma=w;
    }
    double GetSigma()
    {
        return sigma;
    }


private slots:



    void on_buttonBox_accepted();
signals:
    void closed();
private:
    double sigma;
    Ui::AddNoizeDialog *ui;
};

#endif // ADDNOIZEDIALOG_H
