#include "vision.h"
#include <iostream>
Vision::Vision(){
   if (!this->cap.open(0)){
      std::cout << "Cannot open camera" << std::endl;
      exit(-1);
   }
   
}
cv::Mat Vision::getFrame(){
   cv::Mat frame;
   this->cap.read(frame);
   return frame;
}

QImage Vision::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
 
            return image;
         }
 
         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
 
            return image.rgbSwapped();
         }
 
         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;
 
            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }
 
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
 
            image.setColorTable( sColorTable );
 
            return image;
         }
 
         default:
            //qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }
 
      return QImage();
   }