#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    infile=QString("C:/QtProjects/IPf_png/IPpng/Images/Lena.png");
    outfile=QString("C:/QtProjects/IPf_png/IPpng/Images/Lena_f.png");
    ImageHandler=new Handler(infile,outfile);
    QPixmap pict1=QPixmap(infile);
    ImageHandler->ImageRead();
   // FD=new QFileDialog(this);
   // FD->setFileMode(QFileDialog::ExistingFiles);
   // FD->setViewMode(QFileDialog::Detail);
    //FD->setNameFilter(tr("Images (*.png)"));
    scene=new QGraphicsScene(this);
    scene2=new QGraphicsScene(this);
    scene->addPixmap(pict1);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView->setScene(scene2);
   // this->setLayout(ui->horizontalLayout);
    resizeDialog=new Dialog(this);
    connect(resizeDialog,SIGNAL(closed()),this,SLOT(on_dialogClosed()));
    imNoizeDialog=new ImpulseNoizeDialog(this);
    connect(imNoizeDialog,SIGNAL(closed()),this,SLOT(on_imnoizedialogClosed()));
    noizeDialog=new AddNoizeDialog(this);
    connect(noizeDialog,SIGNAL(closed()),this,SLOT(on_noizedialogClosed()));
    convDialog=new ConvolutionDialog(this);
    connect(convDialog,SIGNAL(closed(int)),this,SLOT(on_convDialogClosed(int)));
    binDialog=new BinDialog(this);
    connect(binDialog,SIGNAL(closed()),this,SLOT(on_binDialogClosed()));
    contrastDialog=new GlobContrastDialog(this);
    connect(contrastDialog,SIGNAL(closed()),this,SLOT(on_contrastdialogClosed()));
    m=new QMessageBox(this);
    pb=new QProgressBar(this);
    pb->moveToThread(this->thread());
    pb->hide();
    connect(ImageHandler,SIGNAL(resizeProgressValue(int)),pb,SLOT(setValue(int)));
     connect(ImageHandler,SIGNAL(NLfilterProgressValue(int)),pb,SLOT(setValue(int)));
    connect(ImageHandler,SIGNAL(MedianFiltering()),convDialog,SLOT(on_MedianFilter_opened()));
    connect(ImageHandler,SIGNAL(LinearFiltering()),convDialog,SLOT(on_LinearFilter_opened()));
    setAttribute(Qt::WA_PaintOnScreen);
}

MainWindow::~MainWindow()
{
    delete ImageHandler;
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString str;
    str=QFileDialog::getOpenFileName(this,"Open Input Image","C:/QtProjects/IPf_png/IPpng/Images","Images *.png");
    if (QFile::exists(str))
    {
        infile=str;
    }
    ImageHandler->setInputFile(infile);
    scene->clear();
    scene2->clear();
    QPixmap pict1=QPixmap(infile);
    scene->addPixmap(pict1);
}

void MainWindow::on_dialogClosed()
{
    int w=resizeDialog->GetWidth();
    int h=resizeDialog->GetHeight();
    if ((w!=0)&&(h!=0))
    {
        ui->statusBar->addWidget(pb);
        pb->show();
        ImageHandler->ImageResize(w,h);
        writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->GetOutWidth(),ImageHandler->GetOutHeight(),ImageHandler->GetOutBPP());
        pb->hide();
        ui->statusBar->removeWidget(pb);
    }
    else
    {

        m->setText(QString("Warning!!!Wrong width or height"));
        m->show();
    }
}




void MainWindow::readImage()
{
    ImageHandler->ImageRead();
   //  ImageHandler->ImageReadGray();
}

void MainWindow::writeImage(const char *file, size_t nWidth, size_t nHeight, unsigned int nBPP)
{
    scene2->clear();
    //scene2->setSceneRect(0,0,nWidth,nHeight);
    ImageHandler->ImageWrite(file,nWidth, nHeight, nBPP);
    QPixmap pict2= QPixmap(ImageHandler->getOutputFile());
    scene2->addPixmap(pict2);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->horizontalLayoutWidget->resize(event->size().width()-20,event->size().height()-50);
}

void MainWindow::on_actionInvert_triggered()
{
    ImageHandler->ImageInvert();
    writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,8);
}

void MainWindow::on_actionFloyd_triggered()
{

   ImageHandler->ImageProcessingFloyd();
              #ifdef Floyd8
             writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight, 8);
              #else
             writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight, 2);
              #endif
}

void MainWindow::on_actionResize_triggered()
{
    resizeDialog->show();

   // ImageHandler->ImageResize(dialog);

}

void MainWindow::on_actionAWGN_triggered()
{
    noizeDialog->show();
}

void MainWindow::on_actionImpulse_triggered()
{
    imNoizeDialog->show();
}

void MainWindow::on_actionBlend_triggered()
{
    QString file1=QFileDialog::getOpenFileName(this,"Open Alpha Image","","Images *.png");
    QString file2=QFileDialog::getOpenFileName(this,"Open another (top) image","","Images *.png");
    if(!((QFile::exists(file1))&&(QFile::exists(file2))))
    {
        m->setText(QString("Warning!!!No files selected"));
        m->show();
    }
    else
    {
       ImageHandler->ImageBlending(file1,file2);
       writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,8);
    }
}

void MainWindow::on_noizedialogClosed()
{
    double sig=noizeDialog->GetSigma();
    if (sig>0.0)
    {
        ImageHandler->addAWGN(sig);
        writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,ImageHandler->GetOutBPP());
    }
    else
    {

        m->setText(QString("Warning!!!Wrong value"));
        m->show();
    }
}

void MainWindow::on_convDialogClosed(int flag)
{
    size_t ks=convDialog->getSize();
    float* pk=new float[ks*ks];
    for (int i=0;i<ks;++i)
    {
        for(int j=0;j<ks;++j)
        {
            pk[j+ks*i]=convDialog->getValue(i,j);
        }
    }
    switch(flag)
    {
      case MEDFLTFLAG:
        ImageHandler->ImageMedianFiltering(pk,ks);
        break;
      case LINFLTFLAG:
        ImageHandler->ImageConvolution2D(pk,ks);
        break;
      default:
        m->setText(QString("Error!!!"));
        m->show();
        delete[] pk;
        return;
    }
    delete[] pk;
    writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,8);
}



void MainWindow::on_actionGlobalContrastCalibration_triggered()
{
    contrastDialog->show();
}

void MainWindow::on_contrastdialogClosed()
{
   int ct=contrastDialog->getCT();
   int ht=contrastDialog->getHT();
   ImageHandler->ImageAutoContrastGray(ht,ct);
   writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,8);

}

void MainWindow::on_imnoizedialogClosed()
{
    double *param=new double[4];
    param[0]=imNoizeDialog->getz(0);
    param[1]=imNoizeDialog->getz(1);
    param[2]=imNoizeDialog->getP(0);
    param[3]=imNoizeDialog->getP(1);
    ImageHandler->addImN(param);
    writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,8);
    delete [] param;
}

void MainWindow::on_action2DConvultion_triggered()
{
    emit ImageHandler->LinearFiltering();
    convDialog->show();
}

void MainWindow::on_actionMedianFilter_triggered()
{

    emit ImageHandler->MedianFiltering();
    convDialog->show();
}

void MainWindow::on_binDialogClosed()
{
    byte T=binDialog->GetSigma();
    int L=0;
    if ((T>0)&&(T<256))
    {
        ImageHandler->ImageBinarization(T,&L);
        m->setText(QString::number(L));

       // writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,ImageHandler->GetOutBPP());
          m->show();
    }
    else
    {

        m->setText(QString("Warning!!!Wrong value"));
        m->show();
    }
}

void MainWindow::on_actionBinarization_triggered()
{
    binDialog->show();
}

void MainWindow::on_actionNLmeans_triggered()
{
    int sig=10;
    ui->statusBar->addWidget(pb);
    pb->show();
    ImageHandler->NLmeansFilter(QSize(15,15),QSize(3,3),10*sig,sig);
    writeImage(ImageHandler->getOutputFile().toStdString().c_str(),ImageHandler->in_mWidth,ImageHandler->in_mHeight,ImageHandler->GetOutBPP());
    pb->hide();
    ui->statusBar->removeWidget(pb);
}
