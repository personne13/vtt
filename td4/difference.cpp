#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* ims1, const char* ims2, const char* imdname)
{
  Mat img1 = imread(ims1, CV_LOAD_IMAGE_GRAYSCALE);

	if(!img1.data){
    cout <<  "Could not open file: " << ims1 << std::endl ;
    return;
	}

  Mat img2 = imread(ims2, CV_LOAD_IMAGE_GRAYSCALE);

	if(!img1.data){
    cout <<  "Could not open file: " << ims2 << std::endl ;
    return;
	}

  imwrite(imdname, img1 - img2);
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
