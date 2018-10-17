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
