#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void process(int sigma, const char* ims, const char * imd){
  (void)sigma;
  (void)ims;
  (void)imd;
}

void usage (const char *s) {
  std::cerr<<"Usage: "<<s<<" r ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int main( int argc, char* argv[] ){
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), argv[2], argv[3]);
  return EXIT_SUCCESS;
}
