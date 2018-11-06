#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};

int distMax(int x, int y){
  return abs(max(x, y));
}

int normL1(int x, int y){
  return abs(x) + abs(y);
}

int normL2(int x, int y){
  return sqrt(x * x + y * y);
}

void
process(const int shape, const int halfsize, const char* imdname)
{
  Mat dst = Mat::zeros(cv::Size(2 * halfsize + 1, 2 * halfsize + 1), CV_8U);

  if( shape == SQUARE ){
    for(int i = 0; i < dst.rows; i++){
      for(int j = 0; j < dst.cols; j++){
        if(distMax(i - dst.rows / 2, j - dst.cols / 2) <= halfsize){
          dst.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  else if( shape == DIAMOND ){
    for(int i = 0; i < dst.rows; i++){
      for(int j = 0; j < dst.cols; j++){
        if(normL1(i - dst.rows / 2, j - dst.cols / 2) <= halfsize){
          dst.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  else if( shape == DISK ){
    for(int i = 0; i < dst.rows; i++){
      for(int j = 0; j < dst.cols; j++){
        if(normL2(i - dst.rows / 2, j - dst.cols / 2) < halfsize){
          dst.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  else if(shape == LINE_V){
    for(int i = 0; i < dst.rows; i++){
      dst.at<uchar>(i, halfsize) = 255;
    }
  }
  else if(shape == DIAG_R){
    for(int i = 0; i < dst.rows; i++){
      dst.at<uchar>(dst.rows - i - 1, i) = 255;
    }
  }
  else if(shape == LINE_H){
    for(int i = 0; i < dst.cols; i++){
      dst.at<uchar>(halfsize, i) = 255;
    }
  }
  else if(shape == DIAG_L){
    for(int i = 0; i < dst.rows; i++){
      dst.at<uchar>(i, i) = 255;
    }
  }
  else if(shape == CROSS){
    for(int i = 0; i < dst.cols; i++){
      dst.at<uchar>(i, dst.rows - i - 1) = 255;
      dst.at<uchar>(dst.rows - i - 1, i) = 255;
    }
  }
  else if(shape == PLUS){
    for(int i = 0; i < dst.cols; i++){
      dst.at<uchar>(halfsize, i) = 255;
      dst.at<uchar>(i, halfsize) = 255;
    }
  }

  imwrite(imdname, dst);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" shape halfsize se-name"<<endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3]);
  return EXIT_SUCCESS;
}
