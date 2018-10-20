#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define EPSILON 2

void
process(const char* imsname)
{
  (void) imsname;
  Mat rgb[3];
  Mat YCrCb[3];
	Mat image_src = imread(imsname, CV_LOAD_IMAGE_COLOR);


	if(!image_src.data){
    cout <<  "Could not open or find the image" << std::endl ;
    return;
	}

	split(image_src, rgb);
	imshow("B", rgb[0]);
	imshow("G", rgb[1]);
	imshow("R", rgb[2]);


  Mat gray;
  cvtColor(image_src, gray, COLOR_RGB2GRAY);
  imshow("RGBtoGRAY", gray);



  Mat ycrcb;
  cvtColor(image_src,ycrcb,COLOR_BGR2YCrCb);
  split(ycrcb, YCrCb);
	imshow("Y", YCrCb[0]);
	imshow("Cr", YCrCb[1]);
	imshow("Cb", YCrCb[2]);

  Mat rgb2ycrcb2rgb;
  cvtColor(ycrcb, rgb2ycrcb2rgb, COLOR_YCrCb2BGR);
  imshow("RGB->YCrCb->RGB", rgb2ycrcb2rgb);

  if(norm(gray, YCrCb[0], NORM_INF) < EPSILON){
    cout << "Both images Y and gray color are the same" << endl;
  }
  else{
    cout << "Both images Y and gray color are different" << endl;
  }

  if(norm(image_src, rgb2ycrcb2rgb, NORM_INF) < EPSILON){
    cout << "Base and converted images are the same" << endl;
  }
  else{
    cout << "Base and converted images are different" << endl;
  }

  waitKey(0);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;
}
