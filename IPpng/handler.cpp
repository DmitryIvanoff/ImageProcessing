#include "handler.h"
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QGenericMatrix>
Handler::Handler(QString in_file, QString out_file, QObject *parent) : QObject(parent)
{
    inFile =in_file;
    outFile=out_file;
    pInputBits=0;
    pOutputBits=NULL;
    in_mWidth=0;
    in_mHeight=0;
    in_mBPP=0;
    out_mWidth=0;
    out_mHeight=0;
    out_mBPP=0;
    InputSize=OutputSize=0;


}

Handler::~Handler()
{
    if (pInputBits)
        delete[] pInputBits;
    if (pOutputBits)
        delete[] pOutputBits;
}

void Handler::setInputFile(QString f)
{
    inFile=f;
    if (pInputBits)
        delete[] pInputBits;
    ImageRead();
    outFile=inFile;
}
//-----------------------
void Handler::ImageInvert()
{
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_inv");
    outFile+=QString(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    OutputSize=InputSize;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[OutputSize];

    }
    ImageInvert(pOutputBits,pIn, in_mWidth, in_mHeight,in_mBPP);
    if (pIn)
       delete pIn;
    qDebug()<<"Invert";
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
}

void Handler::ImageProcessing()
{
    //ImageProcessingGray(pOutputBits,pInputBits, out_mWidth, out_mHeight,out_mBPP);
}

void Handler::ImageProcessingFloyd()
{
     byte* pIn=CopyBits(pInputBits,InputSize);
     #ifdef Floyd8
        OutputSize=InputSize;
     #else
        OutputSize=InputSize/4;
     #endif
     if (pOutputBits)
     {
         delete [] pOutputBits;
         pOutputBits=new byte[OutputSize];
     }
     QString str = inFile;
     outFile=str.remove(QString(".png"))+QString("_Floyd")+QString::number(qrand());
     outFile+=QString(".png");
     ImageProcessingFloyd(pOutputBits,pIn, in_mWidth, in_mHeight,in_mBPP);
     if (pIn)
        delete pIn;
     qDebug()<<"Floyd";
     qDebug()<<"Входной размер: "<<InputSize<<" bytes";
     qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
}


void Handler::ImageRead()
{

    InputSize=ImageRead(inFile.toStdString().c_str(),pInputBits,&in_mWidth,&in_mHeight,&in_mBPP);
    qDebug()<<"Входное изображение:";
    qDebug()<<in_mWidth<<"x"<<in_mHeight;
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    OutputSize=InputSize;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[OutputSize];
    }
    else
    {
        pOutputBits=new byte[OutputSize];
    }
}


void Handler::ImageWrite(const char *file
                         , size_t nWidth
                         , size_t nHeight
                         , unsigned int nBPP)
{
    ImageWrite(file, pOutputBits, nWidth, nHeight, nBPP);
}

void Handler::ImageResize(size_t outWidth, size_t outHeight)
{

    out_mWidth=outWidth;
    out_mHeight=outHeight;
    out_mBPP=in_mBPP;
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_resized");
    outFile+=QString(".png");
    OutputSize=(out_mHeight*out_mWidth);
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[OutputSize];
    }
    resizeImage(pOutputBits,pInputBits,in_mWidth,in_mHeight,out_mWidth,out_mHeight);
    qDebug()<<"resize";
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
}

void Handler::addAWGN(double sig)
{
    qDebug()<<"addAWGN";
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_AWGN");
    outFile+=QString(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[InputSize];
    }

    addAWGN(sig,pOutputBits,pIn, in_mWidth, in_mHeight,in_mBPP);
    if (pIn)
        delete pIn;
}

void Handler::ImageBlending(QString& alpha, QString& image)
{
     byte* pAlpha;
     byte* pImg;
     size_t w;
     size_t h;
     unsigned int bpp;
     ImageRead(alpha.toStdString().c_str(),pAlpha,&w,&h,&bpp);
     ImageRead(image.toStdString().c_str(),pImg,&w,&h,&bpp);
     QString str = inFile;
     outFile=str.remove(QString(".png"))+QString("_Blended");
     outFile+=QString(".png");
     byte* pIn=CopyBits(pInputBits,InputSize);
     out_mBPP=in_mBPP;
     if (pOutputBits)
     {
         delete [] pOutputBits;
         pOutputBits=new byte[InputSize];
     }

     ImageBlending(pAlpha,pImg,pOutputBits,pIn,in_mWidth,in_mHeight);
     if (pIn)
         delete pIn;
}

void Handler::ImageAutoContrastGray(int HT, int CT)
{
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_AutoContrasted");
    outFile+=QString(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[InputSize];
    }
    AutoContrastGray(pOutputBits,pIn,in_mWidth,in_mHeight,HT,CT);
    if (pIn)
        delete pIn;
}

void Handler::ImageConvolution2D(const float *kernel, int kernelsize)
{
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_LF");
    outFile+=QString(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[InputSize];
    }
    Convolution2D(pOutputBits,pIn,in_mWidth,in_mHeight,kernel,kernelsize);
    if (pIn)
        delete pIn;
}

void Handler::ImageMedianFiltering(const float * filtermask, int apsize)
{
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_MF");
    outFile+=QString(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[InputSize];
    }
    MedianFilter(pOutputBits,pIn,in_mWidth,in_mHeight,filtermask,apsize);
    if (pIn)
        delete pIn;
}

void Handler::addImN(double* param)
{
    qDebug()<<"addImN";
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_ImN");
    outFile+=(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[InputSize];
    }

    addImN(param,pOutputBits,pIn, in_mWidth, in_mHeight,in_mBPP);
    if (pIn)
        delete pIn;
}

void Handler::ImageBinarization(byte T, int *L)
{
    qDebug()<<"addImN";
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_bin");
    outFile+=(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    OutputSize=(InputSize);
    if (pOutputBits)
    {
        delete [] pOutputBits;
        pOutputBits=new byte[OutputSize];
    }
    ImageBinarization(T,pOutputBits,pIn, in_mWidth, in_mHeight,in_mBPP);
    *L=ImageCountRealms(pOutputBits,in_mWidth, in_mHeight);
    qDebug()<<L;
    if (pIn)
        delete pIn;
}

void Handler::NLmeansFilter(QSize slWinSize, QSize blockSize, double h, double sig)
{
    qDebug()<<"addImN";
    qDebug()<<"Входной размер: "<<InputSize<<" bytes";
    qDebug()<<"Выходной размер: "<<OutputSize<<" bytes";
    QString str = inFile;
    outFile=str.remove(QString(".png"))+QString("_NLmeansFilter");
    outFile+=(".png");
    byte* pIn=CopyBits(pInputBits,InputSize);
    out_mBPP=in_mBPP;
    OutputSize=(InputSize);
    pOutputBits=pIn;
    NLmeans(pOutputBits,pInputBits,in_mWidth, in_mHeight,slWinSize, blockSize,  h, sig) ;

}



//-------------------------
//private:

void Handler::ImageBlending(byte *pA, byte *pImg, byte *pOut, byte *pIn, size_t nWidth, size_t nHeight)
{
    for (size_t y = 0; y < nHeight; ++y)
    {
        for (size_t x = 0; x < nWidth; ++x)
        {
            double t=(*pA++)/255.0;
            (*pOut++) = (1-t)*(*pIn++)+(*pImg++)*t;
        }
    }
}
void Handler::ImageProcessingFloyd(byte *pOut, byte *pIn, size_t nWidth, size_t nHeight, unsigned int nBPP)
{
    // ASSERT(pOut != NULL && pIn != NULL && nWidth > 0 && nHeight > 0)
    float err=0;
    #ifdef Floyd8
    #else
       int k=0;
    #endif
    switch (nBPP)
    {
      case 8:

            for (size_t y = 0; y < nHeight; ++y)
            {
                for (size_t x = 0; x < nWidth; ++x)
                {
                    if( *pIn > 191 )
                    {
                         err = *pIn-255;
                   #ifdef Floyd8
                         *pOut=255;
                   #else
                         *pOut|=(1<<(7-2*k));
                         *pOut|=(1<<(6-2*k));
                   #endif
                    }
                    else
                    {
                        if( *pIn>127)
                        {
                            err = *pIn-255;
                            *pOut|=(1<<(7-2*k));
                        }
                        else
                        {
                        if( *pIn > 63 )
                        {
                             err = *pIn-0;
                       #ifdef Floyd8
                             *pOut=255;
                       #else
                             //*pOut|=(1<<(7-2*k));
                             *pOut|=(1<<(6-2*k));
                       #endif
                        }
                        else
                        {
                        err = *pIn-0;
                       #ifdef Floyd8
                         *pOut=0;
                       #else

                       #endif
                        }
                        }
                    }
                    if ((y<(nHeight-1))&&(x<(nWidth-1)))
                    {

                      if (err>0)
                      {
                         *(pIn+1)= (255>(*(pIn+1)+(7.0/16.0 * err))?(*(pIn+1)+(7.0/16.0 * err)) : 255);
                         *(pIn+1+nWidth)=255>(*(pIn+1+nWidth)+(1.0/16.0 * err))?(*(pIn+1+nWidth)+(1.0/16.0 * err)) : 255;
                         *(pIn+nWidth)= 255>(*(pIn+nWidth)+(5.0/16.0 * err))?(*(pIn+nWidth)+(5.0/16.0 * err)) : 255;
                         *(pIn+nWidth-1)= 255>(*(pIn-1+nWidth)+(3.0/16.0 * err))?(*(pIn-1+nWidth)+(3.0/16.0 * err)) : 255;
                      }
                      else
                      {

                          *(pIn+1)= 0<(*(pIn+1)+(7.0/16.0 * err))?(*(pIn+1)+(7.0/16.0 * err)) : 0;
                          *(pIn+1+nWidth)=0<(*(pIn+1+nWidth)+(1.0/16.0 * err))?(*(pIn+1+nWidth)+(1.0/16.0 * err)) : 0;
                          *(pIn+nWidth)= 0<(*(pIn+nWidth)+(5.0/16.0 * err))?(*(pIn+nWidth)+(5.0/16.0 * err)) : 0;
                          *(pIn+nWidth-1)= 0<(*(pIn-1+nWidth)+(3.0/16.0 * err))?(*(pIn-1+nWidth)+(3.0/16.0 * err)) : 0;
                      }
                    }
                    else
                    {
                        if ((x==(nWidth-1))&&(y<(nHeight-1)))
                        {
                            if (err>0)
                            {
                               *(pIn+nWidth)= 255>(*(pIn+nWidth)+(5.0/16.0 * err))?(*(pIn+nWidth)+(5.0/16.0 * err)) : 255;
                               *(pIn+nWidth-1)= 255>(*(pIn-1+nWidth)+(3.0/16.0 * err))?(*(pIn-1+nWidth)+(3.0/16.0 * err)) : 255;
                            }
                            else
                            {
                                *(pIn+nWidth)= 0<(*(pIn+nWidth)+(5.0/16.0 * err))?(*(pIn+nWidth)+(5.0/16.0 * err)) : 0;
                                *(pIn+nWidth-1)= 0<(*(pIn-1+nWidth)+(3.0/16.0 * err))?(*(pIn-1+nWidth)+(3.0/16.0 * err)) : 0;
                            }
                        }
                        else
                        {
                           if ((x<(nWidth-1))&&(y==(nHeight-1)))
                           {
                               if (err>0)
                               {
                                   *(pIn+1)= (255>(*(pIn+1)+(7.0/16.0 * err))?(*(pIn+1)+(7.0/16.0 * err)) : 255);

                               }
                               else
                               {
                                   *(pIn+1)= 0<(*(pIn+1)+(7.0/16.0 * err))?(*(pIn+1)+(7.0/16.0 * err)) : 0;
                               }
                           }
                        }

                    }
                    #ifdef Floyd8
                          pOut++;
                    #else
                       if (k==3)
                       {
                          ++pOut;
                          k=0;
                       }
                       else
                       {
                          ++k;
                       }
                    #endif
                    ++pIn;
               }

           }
          break;
    case 24:
           break;
//
    }
    return;
}

void Handler::ImageInvert(byte* pOut
             , byte* pIn
             , size_t nWidth
             , size_t nHeight,
              unsigned int nBPP)
{
    // ASSERT(pOut != NULL && pIn != NULL && nWidth > 0 && nHeight > 0)
   // for example, inversion of image
    switch (nBPP)
    {
       case 8:
        for (size_t y = 0; y < nHeight; ++y)
        {
            for (size_t x = 0; x < nWidth; ++x)
            {
                *pOut++ = 255 - *pIn++;
            }
        }
        return;
         break;
    case 24:
        for (size_t y = 0; y < nHeight; ++y)
        {
            for (size_t x = 0; x < nWidth; ++x)
            {
                *pOut++ = 255 - *pIn;
                pIn=pIn+3;
            }
        }
         break;

    }


}

size_t Handler::ImageRead(const char *file, byte*& pBuf
                        , size_t*	pWidth
                        , size_t*	pHeight
                        , unsigned int* pBPP)
{
    size_t nReqSize = NPngProc::readPngFile(file, 0, pWidth, pHeight,pBPP);
      if (nReqSize == NPngProc::PNG_ERROR)
      {
          qDebug()<<"\nError occured while pngfile was read";
          exit(1);
      }
      pBuf = new byte[nReqSize];
      if (!pBuf)
      {
          qDebug()<<"\nCan't allocate memory for image, required size is %u"<< nReqSize;
          exit(1);
      }
      nReqSize = NPngProc::readPngFile(file, pBuf, pWidth, pHeight,pBPP);//по умолчанию 8bpp
   // size_t nRetSize = NPngProc::readPngFileGray(szInputFileName, pInputBits, &nWidth, &nHeight, &nBPP);

     return nReqSize;

}


void Handler::ImageWrite(const char *file, byte *pBuf, size_t nWidth, size_t nHeight, unsigned int nBPP)
{

    size_t s;
    s=NPngProc::writePngFile(file, pBuf, nWidth,nHeight, nBPP,0);
    if (s== NPngProc::PNG_ERROR)
    {
        qDebug()<<"\nError occured during png file was written";
        exit(1);
    }
}



float Handler::CubicInterpolate(const float *points, int n, float val, byte sector)
{
    //n- число точек
    //val [0;n-1] (n-1 сегментов сплайна)
   n=4;
   float* d=new float[n];
   d[0]=(points[1]-points[0])/2;
   d[n-1]=(points[n-1]-points[n-2])/2;
   float* R=new float[n];
   R[0]=(points[1]-points[0])/2;
   R[n-1]=(points[n-1]-points[n-2])/2;
   for(int i=1;i<n-1;++i)
   {
       R[i]=3*(points[i+1]-points[i-1]);
   }
   //QGenericMatrix<1,n,int> n();
   QMatrix4x4 mat(1.0,0.0,0.0,0.0,
                  1.0,4.0,1.0,0.0,
                  0.0,1.0,4.0,1.0,
                  0.0,0.0,0.0,1.0);
   QMatrix4x4 inv;
   for (int i=0;i<4;++i)
   {
       for (int j=0;j<4;++j)
       {
           inv(i,j)= mat.inverted()(i,j);
       }
   }
   for(int i=0;i<n;++i)
    {
          d[1]+=inv(1,i)*R[i];
          d[2]+=inv(2,i)*R[i];
   }
   float* F=new float[4];
   F[0]=2*powf(val,3)-3*powf(val,2)+1;
   F[1]=(-2)*powf(val,3)+3*powf(val,2);
   F[2]=(powf(val,3)-2*powf(val,2)+val);
   F[3]=powf(val,3)-powf(val,2);
   float r=points[sector-1]*F[0]+points[sector]*F[1]+d[sector-1]*F[2]+d[sector]*F[3];
   delete[] d;
   delete[] R;
   delete[] F;
   return r;
}

float Handler::CubicInterpolate(const int *points, int n, float val, byte sector)
{
    //n- число точек
    //val [0;n-1] (n-1 сегментов сплайна)
   n=4;
   float* d=new float[n];
   d[0]=(points[1]-points[0])/2;
   d[n-1]=(points[n-1]-points[n-2])/2;
   float* R=new float[n];
   R[0]=(points[1]-points[0])/2;
   R[n-1]=(points[n-1]-points[n-2])/2;
   for(int i=1;i<n-1;++i)
   {
       R[i]=3*(points[i+1]-points[i-1]);
   }

   //QGenericMatrix<1,n,int> n();
 /*  QMatrix4x4 mat(1.0,0.0,0.0,0.0,
                  1.0,4.0,1.0,0.0,
                  0.0,1.0,4.0,1.0,
                  0.0,0.0,0.0,1.0);
   QMatrix4x4 inv;
   for (int i=0;i<4;++i)
   {
       for (int j=0;j<4;++j)
       {
           inv(i,j)= mat.inverted()(i,j);
           qDebug()<<inv(i,j);
       }
       qDebug()<<"\n";
   }*/
   float inv[2][4]={-0.26666 ,0.26666, -0.06666, 0.066666,
              0.06666, -0.06666, 0.26666, -0.266666};


   /*for(int i=0;i<n;++i)
    {
          d[1]+=inv(1,i)*R[i];
          d[2]+=inv(2,i)*R[i];
   }*/
   for(int i=0;i<n;++i)
   {
       d[1]+=inv[0][i]*(R[i]);
       d[2]+=inv[1][i]*(R[i]);
   }
   delete [] R;
   float* F=new float[n];
   float v3=powf(val,3);
   float v2=powf(val,2);
   F[0]=2*v3-3*v2+1;
   F[1]=(-2)*v3+3*v2;
   F[2]=v3-2*v2+val;
   F[3]=v3-v2;
   float r=points[sector-1]*F[0]+points[sector]*F[1]+d[sector-1]*F[2]+d[sector]*F[3];
   delete [] d;
   delete [] F;
   return r;

}

float Handler::BicubicInterpolate(int** points, float x, float y,byte sector_x,byte sector_y)
{
   float* tmp = new float[4];
// qDebug()<<"Bicubic 0";
   tmp[0]=CubicInterpolate(points[0],4,x,sector_x);
  //  qDebug()<<"Bicubic 1"<<tmp[0];
   tmp[1]= CubicInterpolate(points[1],4,x,sector_x);
 //  qDebug()<<"Bicubic 2"<<tmp[1];
   tmp[2]= CubicInterpolate(points[2],4,x,sector_x);
  // qDebug()<<"Bicubic 3"<<tmp[2];
   tmp[3]= CubicInterpolate(points[3],4,x,sector_x);
  // qDebug()<<"Bicubic 3"<<tmp[3];
   float r1=CubicInterpolate(tmp,4,y,sector_y);
   //qDebug()<<r1;
   delete[] tmp;
   return r1;
}

int Handler::NeibourInterpolation(int** points, float x, float y)
{
    if (x>0.5)
    {

        if (y>0.5)
        {
            return points[2][2];
        }
        else
        {
            return points[1][2];
        }
    }
    else
    {
        if (y>0.5)
        {
            return points[2][1];
        }
        else
        {
            return points[1][1];
        }
    }
}
void Handler::resizeImage(byte *pOut,
                          byte *pIn,
                          size_t inWidth,
                          size_t inHeight,
                          size_t outWidth,
                          size_t outHeight)
{
    float** mat=new float*[2];
    byte sector_x,sector_y;
    for (int i=0;i<2;++i)
    {
        mat[i]=new float[2];
    }
    mat[0][0]=(float)inWidth/(float)outWidth;
    mat[0][1]=0;
    mat[1][0]=0;
    mat[1][1]=(float)inHeight/(float)outHeight;
    for (size_t j = 0; j < outHeight; ++j)
    {
        float y=j*mat[1][1];
        size_t y_i=(size_t)truncf(y);
        if ((y_i>0)&&(y_i<(inHeight-2)))
        {
            sector_y=2;
        }
        else
        {
            if (y_i==0)
            {
                sector_y=1;
            }
            else
            {
                if (y_i>=(inHeight-2))
                {
                    sector_y=3;
                }

            }
        }
        for (size_t i = 0; i < outWidth; ++i)
        {
            float x=i*mat[0][0];
            size_t x_i=(size_t)truncf(x);
            if ((x_i>0)&&(x_i<(inWidth-2)))
            {
                sector_x=2;
            }
            else
            {
                if (x_i==0)
                {
                    sector_x=1;
                }
                else
                {
                    if (x_i>=(inWidth-2))
                    {
                        sector_x=3;
                    }

                }
            }
            int** points=new int*[4];
            for (int l=0;l<4;++l)
            {
                points[l]=new int[4];
            }
            for (int k=0;k<4;++k)
              {
                  for(int q=0;q<4;++q)
                   {
                      if (y_i>(inHeight-4))
                      {

                         if (x_i>inWidth-4)
                         {
                           points[q][k]=*(pIn+(inWidth-4)+k+((inHeight-4)+q)*inWidth);
                         }
                         else
                         {
                             points[q][k]=*(pIn+x_i+k+((inHeight-4)+q)*inWidth);
                         }
                      }
                      else
                      {
                          if (x_i>inWidth-4)
                          {
                              points[q][k]=*(pIn+(inWidth-4)+k+((y_i)+q)*inWidth);
                          }
                          else
                          {
                              points[q][k]=*(pIn+(x_i)+k+((y_i)+q)*inWidth);
                          }

                      }
                   }
                }

            byte b;
            float r=NeibourInterpolation(points,x-truncf(x),y-truncf(y));//BicubicInterpolate(points,x-truncf(x),y-truncf(y),sector_x,sector_y);
            b=(unsigned char)r;
            if (r>255)
            {
                b=255;
            }
            else
            {
               if (r<0)
               {
                   b=0;
               }
            }
            *(pOut)=b;
            for (int l=0;l<4;++l)
            {
               delete [] points[l];
            }
            ++pOut;
            float res=(float)((j+1)*outWidth+(i+1))/(float)(outHeight*outWidth);
            emit resizeProgressValue(((res)*100.0));

        }
    }
    for (int i=0;i<2;++i)
    {
       delete [] mat[i];
    }
}

Handler::byte* Handler::CopyBits(byte *p,size_t size)
{
    byte* t=new byte[size];
    for (int i=0;i<size;++i)
    {
        t[i]=p[i];
    }
    return t;
}

void Handler::addAWGN(double sigma,
                      byte *pOut,
                      byte *pIn,
                      size_t nWidth,
                      size_t nHeight,
                      unsigned int nBPP)
{
    NoizeAWGN* AWGN=new NoizeAWGN(this,0,sigma);
    switch (nBPP)
    {
       case 8:
        for (size_t y = 0; y < nHeight; ++y)
        {
            for (size_t x = 0; x < nWidth; ++x)
            {

                //double a=AWGN->noize();
                double a;
               #ifdef CORRELATED
                a=AWGN->noize();
                if ((y<(nHeight-1))&&(x<(nWidth-1)))
                {

                  if (a>0)
                  {
                     *(pIn+1)= (255>(*(pIn+1)+(7.0/16.0 *a))?(*(pIn+1)+(7.0/16.0 * a)) : 255);
                     *(pIn+1+nWidth)=255>(*(pIn+1+nWidth)+(1.0/16.0 * a))?(*(pIn+1+nWidth)+(1.0/16.0 * a)) : 255;
                     *(pIn+nWidth)= 255>(*(pIn+nWidth)+(5.0/16.0 * a))?(*(pIn+nWidth)+(5.0/16.0 * a)) : 255;
                     *(pIn+nWidth-1)= 255>(*(pIn-1+nWidth)+(3.0/16.0 * a))?(*(pIn-1+nWidth)+(3.0/16.0 * a)) : 255;
                  }
                  else
                  {

                      *(pIn+1)= 0<(*(pIn+1)+(7.0/16.0 * a))?(*(pIn+1)+(7.0/16.0 * a)) : 0;
                      *(pIn+1+nWidth)=0<(*(pIn+1+nWidth)+(1.0/16.0 * a))?(*(pIn+1+nWidth)+(1.0/16.0 * a)) : 0;
                      *(pIn+nWidth)= 0<(*(pIn+nWidth)+(5.0/16.0 * a))?(*(pIn+nWidth)+(5.0/16.0 *a)) : 0;
                      *(pIn+nWidth-1)= 0<(*(pIn-1+nWidth)+(3.0/16.0 * a))?(*(pIn-1+nWidth)+(3.0/16.0 * a)) : 0;
                  }
                }
                else
                {
                    if ((x==(nWidth-1))&&(y<(nHeight-1)))
                    {
                        if (a>0)
                        {
                           *(pIn+nWidth)= 255>(*(pIn+nWidth)+(5.0/16.0 * a))?(*(pIn+nWidth)+(5.0/16.0 * a)) : 255;
                           *(pIn+nWidth-1)= 255>(*(pIn-1+nWidth)+(3.0/16.0 * a))?(*(pIn-1+nWidth)+(3.0/16.0 * a)) : 255;
                        }
                        else
                        {
                            *(pIn+nWidth)= 0<(*(pIn+nWidth)+(5.0/16.0 * a))?(*(pIn+nWidth)+(5.0/16.0 * a)) : 0;
                            *(pIn+nWidth-1)= 0<(*(pIn-1+nWidth)+(3.0/16.0 * a))?(*(pIn-1+nWidth)+(3.0/16.0 * a)) : 0;
                        }
                    }
                    else
                    {
                       if ((x<(nWidth-1))&&(y==(nHeight-1)))
                       {
                           if (a>0)
                           {
                               *(pIn+1)= (255>(*(pIn+1)+(7.0/16.0 * a))?(*(pIn+1)+(7.0/16.0 * a)) : 255);

                           }
                           else
                           {
                               *(pIn+1)= 0<(*(pIn+1)+(7.0/16.0 * a))?(*(pIn+1)+(7.0/16.0 * a)) : 0;
                           }
                       }
                    }

                }
                *pOut = *pIn;
                pOut++;
                pIn++;
              #else
                a=(*pIn++)+AWGN->noize();
                if (a>255)
                {
                    a=255;
                }
                if (a<0)
                {
                    a=0;
                }
                *pOut++ = a;
              #endif
            }
        }
         break;
    case 24:
        for (size_t y = 0; y < nHeight; ++y)
        {
            for (size_t x = 0; x < nWidth; ++x)
            {
                double a=(*pIn++)+AWGN->noize();
                if (a>255)
                {
                    a=255;
                }
                if (a<0)
                {
                    a=0;
                }
                *pOut++ = a;
                pIn=pIn+3;
            }
        }
         break;

    }
}



void Handler::addImN(double *param,
                     byte *pOut,
                     byte *pIn,
                     size_t nWidth,
                     size_t nHeight,
                     unsigned int nBPP)
{
    NoizeImN* ImNoize=new NoizeImN(this,param[0],param[1],param[2],param[3]);
    switch (nBPP)
    {
       case 8:
        for (size_t y = 0; y < nHeight; ++y)
        {
            for (size_t x = 0; x < nWidth; ++x)
            {
                double a=ImNoize->noize(*pIn);
                if (a>255)
                {
                    a=255;
                }
                if (a<0)
                {
                    a=0;
                }
                *pOut = a;
                 ++pOut;
                 ++pIn;
            }
        }
        return;
         break;
    case 24:
        for (size_t y = 0; y < nHeight; ++y)
        {
            for (size_t x = 0; x < nWidth; ++x)
            {
                double a=ImNoize->noize(*pIn);
                if (a>255)
                {
                    a=255;
                }
                if (a<0)
                {
                    a=0;
                }
                *pOut++ = a;
                pIn=pIn+3;
            }
        }
         break;

    }
}
void Handler::AutoContrastGray(  byte* pOut
                      , byte* pIn
                      , size_t nWidth
                      , size_t nHeight
                      , int HT
                      , int CT)
{
    unsigned long alHist[256],lSum;
    byte abLUT[256];
    float gamma=1.3;
    int i, lLeftLim, lRightLim;
    // вычисление гистограммы яркостей
    memset(alHist, 0, 256*sizeof(long));
    for (int y = 0; y < nHeight; y++)
    {
       for (int x = 0; x < nWidth; x++)
       {
          alHist[pIn[x + nWidth*y]]++;
       }
    }
   // нахождение левой границы для контрастирования
   lSum = 0;
   for (lLeftLim = 0; lLeftLim < 100; lLeftLim++)
   {
    // H0 = H1 = HT см. рис. на предыдущем слайде
    if (alHist[lLeftLim] > HT) break;
    lSum += alHist[lLeftLim];
    // С0 = С1 = СT см. рис. на предыдущем слайде
    if (lSum > CT) break;
   }
// нахождение правой границы для контрастирования
   lSum = 0;
   for (lRightLim = 255; lRightLim > 150; lRightLim--)
   {
     if (alHist[lRightLim] > HT) break;
     lSum += alHist[lRightLim];
      if (lSum > CT) break;
   }
   // вычисление таблицы перекодировки (LUT, Look-Up Table)
   for (i = 0; i < lLeftLim; i++) { abLUT[i] = (byte)0; }
   for (i = lLeftLim; i < lRightLim; i++)
   {
       abLUT[i]=(byte)255*pow(((double)(i-lLeftLim)/(double)(lRightLim-lLeftLim)),gamma);
       if (abLUT[i]>255)
       {
           abLUT[i]=255;
       }
       if (abLUT[i]<0)
       {
           abLUT[i]=0;
       }
   }
   for (i = lRightLim; i < 256; i++) { abLUT[i] = (byte)255; }
   // непосредственно контрастирование
   for (int y = 0; y < nHeight; y++)
   {
      for (int x = 0; x < nWidth; x++)
      {
         pOut[x + nWidth*y] = abLUT[pIn[x + nWidth*y]];
      }
   }
}


void Handler::Convolution2D(byte *pOut, byte *pIn, size_t nWidth, size_t nHeight, const float *pKernel, int iKernelSize)
{
    int iHalf = iKernelSize / 2;
    memcpy( pOut, pIn, sizeof(*pOut) * nWidth * nHeight );
    // копирование изображения (для полос по краям изображения)
    for ( int y = iHalf; y < nHeight - iHalf; ++y )
    { // свертка
       for( int x = iHalf; x < nWidth - iHalf; ++x )
       {
          const float* pk = pKernel;
          const byte* ps = &pIn[(y - iHalf) * nWidth + x - iHalf];
          double iSum = 0.0;
          for ( int v = 0; v < iKernelSize; ++v )
          {
             for ( int u = 0; u < iKernelSize; ++u )
                iSum += (float)(ps[u]) * pk[u];
             pk += iKernelSize; // Переход к следующей строкам
             ps += nWidth;
          }
          if ( iSum > 255 ) iSum = 255; // Контроль выхода из диапазона 8 bpp
          else
             if ( iSum < 0 ) iSum = 0;
                pOut[y * nWidth + x] = (byte)iSum;
       }
    }
}


void Handler::MedianFilter(byte *pOut, byte *pIn, size_t nWidth, size_t nHeight, const float *FilterMask, int ApSize)
{
    int iHalf = ApSize / 2;
    int sum=0;
    const float* pk = FilterMask;
    for ( int i = 0; i < ApSize; ++i )
    { // свертка
       for( int j = 0; j < ApSize; ++j )
       {
           sum+=FilterMask[j+i*ApSize];
       }
    }
    float* ApColors=new float[sum];
    memcpy( pOut, pIn, sizeof(*pOut) * nWidth * nHeight );
    // копирование изображения (для полос по краям изображения)
    for ( int y = iHalf; y < nHeight - iHalf; ++y )
    { // свертка
       for( int x = iHalf; x < nWidth - iHalf; ++x )
       {
          const byte* ps = &pIn[(y - iHalf) * nWidth + x - iHalf];
          const float* pk = FilterMask;
          int med = 0;
          int c=0;
          for ( int v = 0; v < ApSize; ++v )
          {
             for ( int u = 0; u < ApSize; ++u )
             {
                 for(int k=0;k<pk[u];++k)
                 {
                    ApColors[c++]=(float)(ps[u]);
                 }
             }
             pk += ApSize; // Переход к следующей строкам
             ps += nWidth;
          }
          quickSort<float>(ApColors,0,sum-1);
        /*  if (sum%2)
          {
             med=ApColors[(sum)/2];
          }
          else
          {
              int ind=(sum/2);
              med=(int)((ApColors[ind]+ApColors[ind+1])/2.0f);
          }*/
          int ind=sum-1;
          med=(int)(ApColors[0]);
          pOut[y * nWidth + x] = (byte)med;
       }
    }
    delete [] ApColors;
}

void Handler::ImageBinarization(byte T, byte *pOut, byte *pIn, size_t nWidth, size_t nHeight, unsigned int nBPP)
{
    // ASSERT(pOut != NULL && pIn != NULL && nWidth > 0 && nHeight > 0)
    int k=0;
    switch (nBPP)
    {
      case 8:

            for (size_t y = 0; y < nHeight; ++y)
            {
                for (size_t x = 0; x < nWidth; ++x)
                {

                    /*  if(*pIn>T)
                        {
                            *pOut|=(1<<(7-k));
                        }
                        else
                        {

                        }
                        if (k==7)
                        {
                           ++pOut;
                           k=0;
                        }
                        else
                        {
                          ++k;
                        }
                     */
                     if(*pIn>T)
                        {
                            (*pOut)=255;
                        }
                        else
                        {
                            (*pOut)=0;
                        }
                    ++pIn;
                    ++pOut;
               }

           }
          break;
    case 24:
           break;
//
    }
    return;
}

int Handler::ImageCountRealms(byte *pIn, size_t nWidth, size_t nHeight)
{
     int ind=0;
     int L=0;
     int* labels=new int[nWidth*nHeight];
     for(int y = 0; y < nHeight; ++y)
     {
        for(int x = 0; x < nWidth; ++x)
        {

            labels[y*nWidth+x]=0;
        }
     }
     for(int y = 0; y < nHeight; ++y)
     {
        for(int x = 0; x < nWidth; ++x)
        {
            byte A=*pIn;
            byte B=0;
            byte C=0;
            if (x>0)
               B=labels[x-1+y*nWidth];
            if (y>0)
               C=labels[x+(y-1)*nWidth];
             if(A>0)
             {
                if ((B>0)&&(C==0))
                {
                   labels[x+y*nWidth]=B;
                }
                else
                {
                  if ((B==0)&&(C>0))
                  {
                    labels[x+y*nWidth]=C;
                  }
                  else
                  {
                      if ((B>0)&&(C>0))
                      {
                         labels[x+y*nWidth]=B;
                         if (B!=C)
                         {
                             for (int k=(x+y*nWidth-1);k>=0;--k)
                             {
                                 if(labels[k]==C)
                                 {
                                    labels[k]=B;
                                 }
                             }
                             --L;

                         }
                      }
                      else
                      {
                         ++L;
                          ++ind;
                         labels[x+y*nWidth]=ind;
                      }
                  }
                }

            }
         ++pIn;
        }
     }
     delete[] labels;
     return L;

}

void Handler::NLmeans(byte *pOut,byte* pIn, size_t nWidth, size_t nHeight, QSize slWinSize, QSize blockSize, double h, double sig)
{
    int wHalf = slWinSize.width() / 2;
    int hHalf = slWinSize.height() / 2;
    int bwHalf = blockSize.width() / 2;
    int bhHalf = blockSize.height() / 2;
    int loffsetx= wHalf;
    int loffsety= hHalf;
    int roffsetx= 0;
    int roffsety= 0;
    float Sum = 0.0;
    float wSum = 0.0;
    float iSum = 0.0;
    float* e=new float[blockSize.width()*blockSize.height()];
    for ( int k =-bhHalf; k < blockSize.height()-bhHalf; ++k )
    {
       for ( int n = -bwHalf; n < blockSize.width()-bwHalf; ++n )
       {
          e[(k+bhHalf)*blockSize.width()+(n+bwHalf)]=exp((-1.0)*((k*k)+(n*n))/(2*sig*sig));

       }
    }
    float* pW=new float[slWinSize.width()*slWinSize.height()];
   for ( int y =0; y < nHeight ; ++y )
   { // свертка
      if (y>nHeight-hHalf)
      {
         roffsety=y-(nHeight-hHalf);
      }
      if (y<=hHalf)
      {
         loffsety=(hHalf)-y;
      }
      roffsetx=0;
      for( int x = 0; x < nWidth ; ++x )
      {

          if (x<=wHalf)
          {

            loffsetx=(wHalf)-x;
         }
          if (x>nWidth-wHalf)
          {
            roffsetx=x-(nWidth-wHalf);
         }

         const byte* pOutWin = &pIn[(y) * nWidth + x];
         Sum = 0.0;
         wSum = 0.0;
         iSum = 0.0;
         float* pWeights=pW;
         for ( int v = bhHalf; v < (slWinSize.height()-bhHalf-loffsety-roffsety); ++v )
         {
            for ( int u = bwHalf; u <slWinSize.width()-bwHalf-loffsetx-roffsetx; ++u )
            {
                const byte* pBlock = &pOutWin[(v-hHalf+loffsety) * nWidth + u-wHalf+loffsetx ];
                for ( int k = -bhHalf; k < blockSize.height()-bhHalf; ++k )
                {
                   for ( int n = -bwHalf; n < blockSize.width()-bwHalf; ++n )
                   {
                       Sum+= pow(((double)pBlock[k*nWidth+n]-(double)pIn[(y +k)* nWidth + x+n]),2)* e[(k+bhHalf)*blockSize.width()+(n+bwHalf)];

                   }
                }
                pWeights[u+(v)*slWinSize.width()]=exp((-1.0)*Sum/(h*h));
                wSum+=pWeights[u+(v)*slWinSize.width()];
            }
         }
         Sum=0.0;
         pWeights=pW;
         const byte* ps = &pIn[y * nWidth + x];
         for ( int v = bhHalf; v < (slWinSize.height()-bhHalf-loffsety-roffsety); ++v )
         {
            for ( int u = bwHalf; u <slWinSize.width()-bwHalf-loffsetx-roffsetx; ++u )
            {
                iSum += (float)(ps[u+(v)*nWidth]) * pWeights[u+(v)*slWinSize.width()];
            }
         }
         //qDebug()<<iSum;
         float val=(iSum/wSum);
         if ( val > 255 ) val =(byte) 255; // Контроль выхода из диапазона 8 bpp
         else
            if ( val < 0 ) val = (byte) 0;
               pOut[y * nWidth + x] = (byte)val;
         float res=(float)((y)*nWidth+(x))/(float)(nHeight*nWidth);
        emit resizeProgressValue(((res)*100.0));
      }

   }
   delete[] pW;
   delete[] e;
}


