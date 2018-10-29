#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void process(int sigma_s, int sigma_g, const char* ims, const char * imd){
  (void)sigma_s;
  (void)sigma_g;
  (void)ims;
  (void)imd;
}

void usage (const char *s) {
  std::cerr<<"Usage: "<<s<<" r ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int main( int argc, char* argv[] ){
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
  return EXIT_SUCCESS;
}
