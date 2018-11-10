#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(int thmin, int thmax, const char* imsname, const char* imdname)
{
  Mat image_src = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << imsname << std::endl ;
    return;
	}

  for(int i = 0; i < image_src.rows; i++){
    for(int j = 0; j < image_src.cols; j++){
      uchar value;
      if(image_src.at<uchar>(i, j) < (thmin + thmax) / 2)
        value = thmin;
      else
        value = thmax;

      image_src.at<uchar>(i, j) = value;
    }
  }

  imwrite(imdname, image_src);
  cout << "file written: " << imdname << endl;
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" thmin thmax ims imd"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
  return EXIT_SUCCESS;
}
