#ifndef NOIZEDIALOG_H
#define NOIZEDIALOG_H

#include <QDialog>

namespace Ui {
class NoizeDialog;
}
 class NoizeDialog : public QDialog
    {
        Q_OBJECT
    signals:
        closed();
    public:
        explicit NoizeDialog(QWidget *parent = 0);
        ~NoizeDialog();
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

 private:
        double sigma;
        Ui::NoizeDialog *ui;
    };

#endif // NOIZEDIALOG_H
