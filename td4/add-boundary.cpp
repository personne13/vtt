#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void color_contour(Mat &im, Mat &contour) {
  for(int i = 0; i < im.rows; i++){
    for(int j = 0; j < im.cols; j++){

      if (contour.at<uchar>(i, j) == 255) {
        Vec3b & color = im.at<Vec3b>(Point(j,i));
        color[0] = 0;
        color[1] = 0;
        color[2] = 255;
      }
    }
  }
}

void
process(const char* ims1, const char* ims2, const char* imdname)
{
  Mat img_src = imread(ims1, CV_LOAD_IMAGE_COLOR);

	if(!img_src.data){
    cout <<  "Could not open file: " << ims1 << std::endl ;
    return;
	}

  Mat contour = imread(ims2, CV_LOAD_IMAGE_GRAYSCALE);

	if(!contour.data){
    cout <<  "Could not open file: " << ims2 << std::endl ;
    return;
	}

  color_contour(img_src, contour);

  imwrite(imdname, img_src);
  cout << "file written: " << imdname << endl;
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims1 ims2 imd"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2], argv[3]);
  return EXIT_SUCCESS;
}
