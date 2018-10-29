#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void process(const char* ims, int freq){
  (void)ims;
  (void)freq;
}

void usage (const char *s) {
  std::cerr<<"Usage: "<<s<<" r ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int main( int argc, char* argv[] ){
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]));
  return EXIT_SUCCESS;
}
