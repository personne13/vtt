#include <iostream>
#include <cstdlib>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(int h,
	int s,
	int v,
	char* ims,
	char* imd)
{
	Mat hsv[3];
	Mat image_src = imread(ims, CV_LOAD_IMAGE_COLOR);
	Mat img_dst;
	Mat img_hsv;

	if(!image_src.data){
      cout <<  "Could not open or find the image" << std::endl ;
      return;
		}

	cvtColor(image_src,img_hsv,CV_RGB2HSV);

	split(img_hsv, hsv);
	imshow("h", hsv[0]);
	imshow("s", hsv[1]);
	imshow("v", hsv[2]);

	Mat tmp(img_hsv.rows, img_hsv.cols, CV_8UC3, Scalar(h, s, v));
	img_hsv = img_hsv + tmp;
	cvtColor(img_hsv, img_dst, CV_HSV2RGB);
	imwrite(imd, img_dst);

	waitKey(0);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" h s v ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 5
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
  return EXIT_SUCCESS;
}
