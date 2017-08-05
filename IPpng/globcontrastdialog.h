#ifndef GLOBCONTRASTDIALOG_H
#define GLOBCONTRASTDIALOG_H

#include <QDialog>

namespace Ui {
class GlobContrastDialog;
}

class GlobContrastDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GlobContrastDialog(QWidget *parent = 0);
    ~GlobContrastDialog();
    int getHT() const;
    void setHT(int value);

    int getCT() const;
    void setCT(int value);

signals:
    void closed();
private slots:
    void on_buttonBox_accepted();

private:
    int HT;
    int CT;
    Ui::GlobContrastDialog *ui;
};

#endif // GLOBCONTRASTDIALOG_H
