#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void reCenter(Mat &mat){
  int halfx = mat.cols/2;
  int halfy = mat.rows/2;

  Mat tl(mat, Rect(0, 0, halfx, halfy));
  Mat tr(mat, Rect(halfx, 0, halfx, halfy));
  Mat bl(mat, Rect(0, halfy, halfx, halfy));
  Mat br(mat, Rect(halfx, halfy, halfx, halfy));

  Mat tmp;//modify base matrix using side effect
  tl.copyTo(tmp);
  br.copyTo(tl);
  tmp.copyTo(br);

  bl.copyTo(tmp);
  tr.copyTo(bl);
  tmp.copyTo(tr);
}

void computeMagnitude(Mat *splitted, Mat &dst){
  magnitude(splitted[0], splitted[1], dst);
}

void saveMagnitude(Mat &a, string name, bool do_show = true){
  Mat dst = a.clone();
  reCenter(dst);
  dst += Scalar::all(1);
  log(dst, dst);
  normalize(dst, dst, 0, 1, CV_MINMAX);
  dst.convertTo(dst, CV_8UC3, 255);
  imwrite(name, dst);
  if(do_show)
    imshow(name, dst);
}

void computePhase(Mat *splitted, Mat &dst){
  phase(splitted[1], splitted[0], dst);
}

void savePhase(Mat &phi){
  Mat dst = phi.clone();
  reCenter(dst);
  normalize(dst, dst, 0, 1, CV_MINMAX);
  dst.convertTo(dst, CV_8UC3, 255);
  imwrite("phase.png", dst);
  imshow("phase.png", dst);
}

void suppressFreq(Mat &mat, int freq){
  int halfx = mat.cols/2;
  int halfy = mat.rows/2;

  mat.at<float>(halfx - freq, halfy) = 0;
  mat.at<float>(halfx + freq, halfy) = 0;
  mat.at<float>(halfx, halfy - freq) = 0;
  mat.at<float>(halfx, halfy + freq) = 0;
}

void modifyMagnitude(Mat &a, Mat &dst, int freq){
  dst = a.clone();
  (void)freq;
  reCenter(dst);
  suppressFreq(dst, freq);
  reCenter(dst);
  saveMagnitude(dst, "magnitude-modify.png", false);
}

void convertBack(Mat &a, Mat &phi, Mat &dst){
  Mat splitted[2];
  Mat F;
  polarToCart(a, phi, splitted[1], splitted[0]);
  merge(splitted, 2, F);
  dft(F, dst, DFT_INVERSE | DFT_REAL_OUTPUT);
  normalize(dst, dst, 0, 1, CV_MINMAX);
}

void process(const char* ims, int freq){
  (void)ims;
  (void)freq;
  Mat image_src = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << ims << std::endl ;
    return;
	}

  Mat splitted[] = {Mat_<float>(image_src), Mat::zeros(image_src.size(), CV_32F)};
  Mat F;//stores direct fourier transform
  merge(splitted, 2, F);
  dft(F, F);
  split(F, splitted);

  Mat a;//compute magnitude
  computeMagnitude(splitted, a);
  saveMagnitude(a,"magnitude.png");
  Mat modifiedMagnitude;
  modifyMagnitude(a, modifiedMagnitude, freq);

  Mat phi;//compute phase
  computePhase(splitted, phi);
  savePhase(phi);

  Mat inversed;
  convertBack(modifiedMagnitude, phi, inversed);

  inversed.convertTo(inversed, CV_8UC3, 255);
  imwrite("inverse.png", inversed);
  waitKey(0);
}

void usage (const char *s) {
  std::cerr<<"Usage: "<<s<<" ims freq\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int main( int argc, char* argv[] ){
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]));
  return EXIT_SUCCESS;
}
