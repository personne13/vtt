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
