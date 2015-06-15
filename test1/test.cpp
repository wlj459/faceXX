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
  int MAX_KERNEL_LENGTH = 15;

  /// 装载图像
	src = imread( "1.jpg",-1 );

  if( !src.data )
  { return -1; }
  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
  //双边滤波
  for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
         { bilateralFilter ( src, dst, i, i*2, i/2 );
          }
  src = dst;
  /// 转换为灰度图
  cvtColor( src, src_gray, CV_RGB2GRAY );
    //直方图均衡
   // equalizeHist( src_gray, dst );
	//src_gray = dst;

  /// 创建显示窗口
  //namedWindow( window_name, CV_WINDOW_AUTOSIZE );
	
  /// 创建 grad_x 和 grad_y 矩阵
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// 求 X方向梯度
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  /// 求Y方向梯度
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );

  /// 合并梯度(近似)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
  //反色
  row = grad.rows;
  col = grad.cols;
  uchar* data = grad.data;
  step = grad.step/sizeof(uchar);  
for (int i=0; i<row; i++)  
{  
    for (int j=0;j<col; j++)  
    {  
        data[i*step+j] = 255- data[i*step+j];
		if (data[i*step+j]>190)
			data[i*step+j] = 255;
	//	else
		//{
			if ((j<col/7)||((col-j)<col/7)||(i<row/10)||(row-i<row/7)&&((j<col/5)||((col-j)<col/5)))
				data[i*step+j] = 255;
		//}
    }  
}  
  
  //imshow( window_name, src_gray ); 
  imwrite("11.jpg",grad);

  waitKey(0);
  return 0;
  }