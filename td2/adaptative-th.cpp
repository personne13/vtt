#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
#define I1 0
#define I2 255

void threshhold(Mat &image_src, Mat &image_dst, int radius, int constant);

void
process(const char* imsname,
	int radius,
  int constant)
{
  (void) radius;
  (void) constant;

  Mat image_src = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << imsname << std::endl ;
    return;
	}

  Mat hand_threshold = image_src.clone();
  Mat cv_threshold = image_src.clone();
  Mat cv_threshold_gauss = image_src.clone();

  threshhold(image_src, hand_threshold, radius, constant);
  adaptiveThreshold(image_src, cv_threshold, I2, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 2 * radius + 1, constant);
  adaptiveThreshold(image_src, cv_threshold_gauss, I2, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 2 * radius + 1, constant);

  imwrite("th.png", hand_threshold);
  imwrite("th-ocv-mean.png", cv_threshold);
  imwrite("th-ocv-gauss.png", cv_threshold_gauss);

  Mat diff = hand_threshold - cv_threshold;
  imshow("diff", diff);

  waitKey(0);
}

int compute_mean(Mat &image, int i, int j, int radius, int constant){
  int res = 0;
  int nb_neighbors = 0;
  int offset = 2 * radius + 1;

  for(int x = i - offset; x < i + offset; x++){
    for(int y = j - offset; y < j + offset; y++){
      if(x >= 0 && x < image.cols &&
         y >= 0 && y < image.rows){
        res += image.at<uchar>(y, x);
        nb_neighbors++;
      }
    }
  }

  return res / nb_neighbors - constant;
}

void threshhold(Mat &image_src, Mat &image_dst, int radius, int constant) {
  for(int i = 0; i < image_src.cols; i++){
    for(int j = 0; j < image_src.rows; j++){
      if((int)image_dst.at<uchar>(j, i) < compute_mean(image_src, i, j, radius, constant)){
        image_dst.at<uchar>(j, i) = I1;
      }
      else{
        image_dst.at<uchar>(j, i) = I2;
      }
    }
  }
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname radius constant\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]), atoi(argv[3]));
  return EXIT_SUCCESS;
}
