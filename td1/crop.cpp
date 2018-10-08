#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname,
	int i0,
	int j0,
	int w,
	int h)
{
  (void) imsname;
  (void) i0;
  (void) j0;
  (void) w;
  (void) h;


	Mat img_src = imread(imsname, CV_LOAD_IMAGE_COLOR);
	if(!img_src.data){
    cout <<  "Could not open or find the image" << std::endl ;
	  return;
	}

	Mat crop(w, h, CV_8UC3);

	int i, j;
	for (i=0; i<w; i++) {
		for (j=0; j<h; j++) {
			crop.at<Vec3b>(i, j) = img_src.at<Vec3b>(i0 + i, j0 + j);
		}
	}

	Mat img_rect = img_src(Rect(j0, i0, h, w));

	Mat img_diff = crop - img_rect;
	imshow("diff=((crop)-(crop-cv))", img_diff);
	waitKey(0);
	imwrite("crop.png", crop);
	imwrite("crop-ocv.png", img_rect);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname i0 j0 w h\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 5
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
  return EXIT_SUCCESS;
}
