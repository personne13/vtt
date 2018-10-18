#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define NB_INTENSITY 256


void computeHistogram(std::vector<int> &H, Mat &src) {
    for (int j = 0; j < (int)H.size(); j++) {
      H[j] = 0;
    }

    MatIterator_<uchar> end = src.end<uchar>();
    for (MatIterator_<uchar> i = src.begin<uchar>(); i != end; i++) {
      uchar k = i[0]; // image is supposed to be in gray color
      H[k]++;
    }
}


void computeCumulatedNormalizedHistogram(std::vector<float> &Hcn,std::vector<int> &H, float MN) {
  int size = H.size();
  Hcn[0] = H[0]/MN;
  for (int i = 1; i < size; i++) {
    Hcn[i] = Hcn[i-1] + H[i]/MN;
  }

}

void equilibrate(Mat &image_src, std::vector<float> &Hcn) {
  MatIterator_<uchar> end = image_src.end<uchar>();
  for (MatIterator_<uchar> i = image_src.begin<uchar>(); i != end; i++) {
    int k = i[0];
    int kp = (NB_INTENSITY - 1) * Hcn[k];
    i[0] = kp;
  }
}

void process(const char* imsname)
{
  // cout <<(short) (int)3 << endl;
  Mat image_src = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
  Mat resultCv;
  Mat diff;
  if(!image_src.data){
      cout <<  "Could not open or find the image" << std::endl ;
      return;
  }

  Mat handMethod = image_src.clone();
  std::vector<int> H(NB_INTENSITY);
  std::vector<float> Hcn(NB_INTENSITY);
  float MN = handMethod.rows * handMethod.cols;

  computeHistogram(H, handMethod);
  computeCumulatedNormalizedHistogram(Hcn, H, MN);
  equilibrate(handMethod, Hcn);
  imwrite("eq.png", handMethod);

  equalizeHist(image_src, resultCv);
  imwrite("eq-ocv.png", resultCv);

  diff = handMethod - resultCv;
  imwrite("diff.png", diff);
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
