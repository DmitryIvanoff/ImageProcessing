#ifndef HANDLER_H
#define HANDLER_H
#include "PngProc.h"
#include <QObject>
#include <QDebug>
#include <QString>
#include <includ/png.h>
#include "noize.h"
#include <ctime>
#ifndef Floyd8
 #define Floyd
#endif
#ifndef CORRELATED
 #define CORRELATE
#endif
template <class T> void quickSort(T* massive,int a,int b)
{
    if (!(a>b))
    {
    T x=massive[b];
    int i=a-1;
    for (int j=a;j<b;j++)
    {
        if (massive[j]<=x)
        {
            ++i;
            T tmp=massive[j];
            massive[j]=massive[i];
            massive[i]=tmp;
        }
    }
    ++i;
    T tmp=massive[b];
    massive[b]=massive[i];
    massive[i]=tmp;
    quickSort<T>(massive,a,i-1);
    quickSort<T>(massive,i+1,b);
    }
}
class Handler : public QObject
{
    typedef unsigned char byte;
    typedef bool bit;
    Q_OBJECT
public:
    explicit Handler(QString in_file, QString out_file, QObject *parent = 0);
    ~Handler();
    void setInputFile(QString f);
    QString getInputFile()
    {
        return inFile;
    }
    void setOutputFile(QString f)
    {
        outFile=f;
    }
    QString getOutputFile()
    {
        return outFile;
    }
    //char* format;
    void SetOutWidth(size_t w)
    {
        out_mWidth=w;
    }
    size_t GetOutWidth()
    {
        return out_mWidth;
    }
    void SetOutHeight(size_t h)
    {
        out_mHeight=h;
    }
    size_t GetOutHeight()
    {
        return out_mHeight;
    }
    void SetOutBPP(size_t nBpp)
    {
        out_mBPP=nBpp;
    }
    size_t GetOutBPP()
    {
        return out_mBPP;
    }
    size_t in_mWidth, in_mHeight;
    void ImageInvert ();
    void ImageProcessing();
    void ImageProcessingFloyd();
    void ImageRead();
    void ImageWrite( const char *file
                     , size_t nWidth
                     , size_t nHeight
                     , unsigned int nBPP);
    void ImageResize(size_t outWidth, size_t outHeight);
    void addAWGN(double);
    void ImageBlending(QString&,QString&);
    void ImageAutoContrastGray(int HT,int CT);
    void ImageConvolution2D(const float* kernel,int kernelsize);
    void ImageMedianFiltering(const float* ,int);
    void addImN(double*);
    void ImageBinarization(byte T,int* L);
    void NLmeansFilter(QSize slWinSize, QSize blockSize, double h, double sig);

signals:
    void resizeProgressValue(int);
    void NLfilterProgressValue(int);
    void MedianFiltering();
    void LinearFiltering();
private:

    QString outFile;
    QString inFile;
    byte* pInputBits;
    byte* pOutputBits;
    size_t InputSize;
    size_t OutputSize;
    size_t out_mWidth, out_mHeight;
    unsigned int out_mBPP;
    unsigned int in_mBPP;
    void ImageBlending(byte* pA
                       , byte* pImg
                       , byte* pOut
                       , byte* pIn
                       , size_t nWidth
                       , size_t nHeight
                       );
    void ImageProcessingFloyd (byte* pOut
                              , byte* pIn
                              , size_t nWidth
                              , size_t nHeight
                              , unsigned int nBPP);
    void ImageInvert (byte* pOut
                              , byte* pIn
                              , size_t nWidth
                              , size_t nHeight
                              , unsigned int nBPP);
    size_t ImageRead (const char *file
                    , byte *&pBuf
                    , size_t *pWidth
                    , size_t *pHeight
                    , unsigned int *pBPP
                    );
    void ImageWrite(const char *file,byte* pOut
                     , size_t nWidth
                     , size_t nHeight
                     , unsigned int nBPP);
    float CubicInterpolate(const float *points, int n, float val,byte sector);
    float CubicInterpolate(const int *points, int n, float val,byte sector);
    float BicubicInterpolate(int **points, float x, float y, byte sector_x, byte sector_y);
    int NeibourInterpolation(int** points, float x, float y);
    void resizeImage(byte* pOut
                     , byte* pIn
                     , size_t inWidth
                     , size_t inHeight, size_t outWidth, size_t outHeight);
    byte *CopyBits(byte* p, size_t size);
    void addAWGN(double sigma,byte* pOut
                 , byte* pIn
                 , size_t nWidth
                 , size_t nHeight
                 , unsigned int nBPP);
    void addImN(  double * param
                 , byte* pOut
                 , byte* pIn
                 , size_t nWidth
                 , size_t nHeight
                 , unsigned int nBPP);
    void AutoContrastGray(  byte* pOut
                          , byte* pIn
                          , size_t nWidth
                          , size_t nHeight
                          , int HT
                          , int CT);
    void Convolution2D(byte* pOut
                        , byte* pIn
                        , size_t nWidth
                        , size_t nHeight
                        , const float *pKernel
                        , int iKernelSize);
    void MedianFilter(byte *pOut
                      , byte *pIn
                      , size_t nWidth
                      , size_t nHeight
                      , const float *FilterMask
                      , int ApSize);
    void ImageBinarization(byte T
                           , byte *pOut
                           , byte *pIn
                           , size_t nWidth
                           , size_t nHeight
                           , unsigned int nBPP
                           );
    int ImageCountRealms(byte *pIn
                         , size_t nWidth
                         , size_t nHeight
                         );
    void NLmeans(byte *pOut
                 ,byte *pIn
                 , size_t nWidth
                 , size_t nHeight
                 , QSize slWinSize
                 , QSize blockSize
                 , double h
                 , double sig);

public slots:
};

#endif // HANDLER_H
