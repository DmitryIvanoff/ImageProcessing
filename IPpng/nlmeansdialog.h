#ifndef NLMEANSDIALOG_H
#define NLMEANSDIALOG_H

#include <QDialog>

namespace Ui {
class NLmeansDialog;
}

class NLmeansDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NLmeansDialog(QWidget *parent = 0);
    ~NLmeansDialog();
    QSize getWin() const;
    void setWin(const QSize &value);

    QSize getBlock() const;
    void setBlock(const QSize &value);

    int getH() const;
    void setH(int value);

    int getSig() const;
    void setSig(int value);

signals:
    void accepted();
private slots:
    void on_buttonBox_accepted();

private:
    QSize Win;
    QSize block;
    int h;
    int sig;
    Ui::NLmeansDialog *ui;
};

#endif // NLMEANSDIALOG_H
