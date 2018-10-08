#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define WIDTH_OUT_IMG 200
#define HEIGHT_OUT_IMG 100

void
process(const char* imsname, const char* imdname)
{
  Mat image_src;
  image_src = imread(imsname, CV_LOAD_IMAGE_COLOR);

  if(!image_src.data){
      cout <<  "Could not open or find the image" << std::endl ;
      return;
  }
  Mat image_dst(HEIGHT_OUT_IMG, WIDTH_OUT_IMG, CV_8UC3, Scalar(255,0,255));

  cout << imsname << " infos:" << std::endl;
  cout << "width: " << image_src.cols << std::endl;
  cout << "height: " << image_src.rows << std::endl;

  imshow(imsname, image_src);
  imshow(imdname, image_dst);

  waitKey(0);
  destroyWindow(imsname);
  destroyWindow(imdname);

  imwrite(imdname, image_dst);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imdname\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2]);
  return EXIT_SUCCESS;
}
