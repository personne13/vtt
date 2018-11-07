#include <iostream>
#include <cstdlib>

#include <morphology.hpp>

using namespace cv;
using namespace std;

void
process(const char* sename, const char* imsname, const char* imdname)
{
  (void) sename;
  (void) imsname;
  (void) imdname;

  Mat image_src = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << imsname << std::endl ;
    return;
	}

  Mat pattern = imread(sename, CV_LOAD_IMAGE_GRAYSCALE);

	if(!pattern.data){
    cout <<  "Could not open file: " << sename << std::endl ;
    return;
	}

  Mat dilated = image_src.clone();
  Mat closed = image_src.clone();

  mm(pattern, image_src, dilated, maximum);
  mm(pattern, dilated, closed, minimum);

  imwrite(imdname, closed);
  cout << "file written: " << imdname << endl;
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<"im-se ims imd"<<std::endl;
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
