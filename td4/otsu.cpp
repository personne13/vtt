#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void computeHistogram(std::vector<int> &H, Mat &src) {
    for (int j = 0; j < (int)H.size(); j++) {
      H[j] = 0;
    }

    MatIterator_<uchar> end = src.end<uchar>();
    for (MatIterator_<uchar> i = src.begin<uchar>(); i != end; i++) {
      uchar k = i[0];
      H[k]++;
    }
}

float compute_p1(std::vector<int> &H, int t, float MN) {
  float p1 = 0;
  for (int i = 0; i < t; i++) {
    p1 += H[i];
  }
  p1 = p1/MN;
  return p1;
}

float compute_p2(std::vector<int> &H, int t, float MN) {
  float p2 = 0;
  for (int i = t + 1; i < 256; i++) {
    p2 += H[i];
  }
  p2 = p2/MN;
  return p2;
}

float compute_u1(std::vector<int> &H, int t) {
  float u1 = 0;
  float g = 0;
  float d = 0;
  for (int i = 0; i < t; i++) {
    g += H[i];
    d += i * H[i];
  }
  if (g == 0) {
    return 0;
  }
  else {
    u1 = 1/g * d;
    return u1;
  }
}

float compute_u2(std::vector<int> &H, int t) {
  float u2 = 0;
  float g = 0;
  float d = 0;
  for (int i = t + 1; i < 256; i++) {
    g += H[i];
    d += i * H[i];
  }
  if (g == 0) {
    return 0;
  }
  else {
  u2 = 1/g * d;
  return u2;
}
}

float compute_variance (float p1, float p2, float u1, float u2) {
  float result = p1 * p2 * pow((u1 - u2), 2);
  return result;
}

void otsu (Mat &src_gray) {
  std::vector<int> H(256);
  std::vector<float> Hcn(256);
  float MN = src_gray.rows * src_gray.cols;

  computeHistogram(H, src_gray);


  float p_1[256], p_2[256], u_1[256], u_2[256];

  for (int i = 0; i < 255; i++)
  {
    p_1[i] = compute_p1(H, i, MN);
    p_2[i] = compute_p2(H, i, MN);
    u_1[i] = compute_u1(H, i);
    u_2[i] = compute_u2(H, i);
  }

    float variance_max = 0;
  	float best = 0;
  	for (int t = 0; t <= 255; t++)
  	{
      float vk = compute_variance(p_1[t], p_2[t], u_1[t], u_2[t]);

  		if (vk > variance_max)
  		{
  			variance_max = vk;
  			best = t;
  		}
  	}

  	for (int i = 0; i < src_gray.rows; i++)
  	{
  		for (int j = 0; j < src_gray.cols; j++)
  		{
  			if (src_gray.at<uchar>(i, j) <= best)
  			{
  				src_gray.at<uchar>(i, j) = 0;
  			}
  			else
  			{
  				src_gray.at<uchar>(i, j) = 255;
  			}
  		}
  }
}

void
process(const char* imsname)
{

  Mat src_gray = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
  	if(!src_gray.data){
      cout <<  "Could not open or find the image" << std::endl ;
      return;
		}

    otsu(src_gray);

  imwrite("cell-res.png", src_gray);

  // open cv
  // Mat otsu_ocv;
  // int thresh = threshold(src_gray_opencv, otsu_ocv, 0, 255, THRESH_BINARY+THRESH_OTSU);
  // std::cout << "ocv otsu threshold t = " << thresh << std::endl;
  // imshow("otsu-th-ocv", otsu_ocv);
  // imwrite("otsu-th-ocv.png", otsu_ocv);

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
