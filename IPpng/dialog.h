#ifndef DIALOG_H
#define DIALOG_H
#include <stdio.h>
#include <string.h>
#include <QDialog>



namespace Ui {
class Dialog;
}
//------------------
class Dialog : public QDialog
{
    Q_OBJECT
signals:
    void closed();
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void SetWidth(size_t w)
    {
        width=w;
    }
    void SetHeight(size_t h)
    {
        height=h;
    }
    size_t GetHeight()
    {
        return height;
    }
    size_t GetWidth()
    {
        return width;
    }


private slots:
    void on_buttonBox_accepted();



private:
    size_t width;
    size_t height;
    Ui::Dialog *ui;
};

//----------------------------


#endif // DIALOG_H
