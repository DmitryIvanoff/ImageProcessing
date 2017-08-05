#ifndef IMPULSENOIZEDIALOG_H
#define IMPULSENOIZEDIALOG_H

#include <QDialog>

namespace Ui {
class ImpulseNoizeDialog;
}

class ImpulseNoizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImpulseNoizeDialog(QWidget *parent = 0);
    double getP(unsigned char ind) const;
    void setP(double p_a,double p_b);

    double getz(unsigned char ind) const;
    void setz(double a,double b);
    ~ImpulseNoizeDialog();
signals:
    void closed();
private slots:
    void on_buttonBox_accepted();

private:
    double p[2];
    double z[2];
    Ui::ImpulseNoizeDialog *ui;
};

#endif // IMPULSENOIZEDIALOG_H
