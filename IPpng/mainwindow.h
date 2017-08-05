#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include "dialog.h"
#include "addnoizedialog.h"
#include "convolutiondialog.h"
#include "globcontrastdialog.h"
#include "impulsenoizedialog.h"
#include "bindialog.h"
#include "handler.h"
#include <QProgressBar>
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
private slots:
    void on_actionOpen_triggered();
    void on_dialogClosed();
    void readImage();
    void writeImage(const char *file, size_t nWidth, size_t nHeight, unsigned int nBPP);
    void on_actionInvert_triggered();

    void on_actionFloyd_triggered();

    void on_actionResize_triggered();

    void on_actionAWGN_triggered();

    void on_actionImpulse_triggered();

    void on_actionBlend_triggered();
    void on_noizedialogClosed();

    void on_convDialogClosed(int);
    void on_actionGlobalContrastCalibration_triggered();
    void on_contrastdialogClosed();
    void on_imnoizedialogClosed();
    void on_action2DConvultion_triggered();

    void on_actionMedianFilter_triggered();
    void on_binDialogClosed();

    void on_actionBinarization_triggered();

    void on_actionNLmeans_triggered();

private:
   // QFileDialog* FD;
    QGraphicsScene* scene;
    QGraphicsScene* scene2;
    QString infile;
    QString outfile;
    Handler* ImageHandler;
    Ui::MainWindow *ui;
    Dialog *resizeDialog;
    AddNoizeDialog* noizeDialog;
    ImpulseNoizeDialog* imNoizeDialog;
    QMessageBox* m;
    QProgressBar* pb;
    ConvolutionDialog *convDialog;
    GlobContrastDialog *contrastDialog;
    BinDialog* binDialog;

protected:
    void resizeEvent(QResizeEvent* event);
signals:
};

#endif // MAINWINDOW_H
