#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  (void) imsname;
  Mat rgb[3];
  Mat YCbCr[3];
	Mat image_src = imread(imsname, CV_LOAD_IMAGE_COLOR);


	if(!image_src.data){
      cout <<  "Could not open or find the image" << std::endl ;
      return;
		}
    // Mat ycrcb = cv2.cvtColor(img, cv2.COLOR_BGR2YCR_CB)

	split(image_src, rgb);
	imshow("R", rgb[0]);
	imshow("G", rgb[1]);
	imshow("B", rgb[2]);
  Mat ycrcb;
  cvtColor(image_src,ycrcb,COLOR_BGR2YCrCb);
  split(ycrcb, YCbCr);
	imshow("Y", YCbCr[0]);
	imshow("Cr", YCbCr[1]);
	imshow("Cb", YCbCr[2]);

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
