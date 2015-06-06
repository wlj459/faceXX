#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;

/** @function main */
int main( int argc, char** argv )
{

  Mat src, src_gray;
  Mat grad, dst;
  char* window_name = "Sobel Demo - Simple Edge Detector";
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  int c;
  int row, col, channel, step;
  int i, j, k;
  /// װ��ͼ��
	src = imread( "10.jpg" );

  if( !src.data )
  { return -1; }

  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// ת��Ϊ�Ҷ�ͼ
  cvtColor( src, src_gray, CV_RGB2GRAY );

  /// ������ʾ����
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
  //ֱ��ͼ��
   // equalizeHist( src_gray, dst );
	//src_gray = dst;
	
  /// ���� grad_x �� grad_y ����
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// �� X�����ݶ�
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  /// ��Y�����ݶ�
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );

  /// �ϲ��ݶ�(����)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
  imshow( window_name, grad );
  row = grad.rows;
  col = grad.cols;
  uchar* data = grad.data;
  step = grad.step/sizeof(uchar);  
for (int i=0; i<row; i++)  
{  
    for (int j=0;j<col; j++)  
    {  
        data[i*step+j] = 255- data[i*step+j];  
    }  
}  
//ֱ��ͼ����
  
  imshow( window_name, src_gray ); 
  imwrite("10a.jpg",grad);

  waitKey(0);
  return 0;
  }