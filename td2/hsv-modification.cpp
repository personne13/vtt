#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(int h,
	int s,
	int v,
	char* ims,
	char* imd)
{
  (void)  h,
  (void) s,
  (void) v,
  (void) ims,
  (void) imd;

}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" h s v ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 5
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
  return EXIT_SUCCESS;
}
