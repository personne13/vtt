#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname,
	int radius,
  int constant)
{
  (void) imsname;
  (void) radius;
  (void) constant;
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
