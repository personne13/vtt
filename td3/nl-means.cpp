#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define V 5 // neighbors
#define R 3 // Pattern

float compute_w(Mat &img_src, int sigma, int i, int j, int k, int l){
  float dist = 0;

  for(int u = -R; u < R + 1; u++){
    for(int v = -R; v < R + 1; v++){
      if(j + u >= 0 && j + u < img_src.rows &&
         i + v >= 0 && i + v < img_src.cols &&
         l + u >= 0 && l + u < img_src.rows &&
         k + v >= 0 && k + v < img_src.cols){
           dist += pow(img_src.at<uchar>(j + u, i + v) - img_src.at<uchar>(l + u, k + v), 2);
       }
    }
  }

  dist /= ((2 * R + 1) * (2 * R + 1));

  return exp(-dist / (2 * sigma * sigma));
}

void nlmeans(Mat &img_src, Mat &img_dst, int sigma){
  for(int i = 0; i < img_src.cols; i++){
    for(int j = 0; j < img_src.rows; j++){
      float num = 0;
      float den = 0;
      for(int k = i - V; k < i + V + 1; k++){
        for(int l = j - V; l < j + V + 1; l++){
          if(k >= 0 && k < img_src.cols &&
             l >= 0 && l < img_src.rows){
              float w = compute_w(img_src, sigma, i, j, k, l);
              num += w * img_src.at<uchar>(l, k);
              den += w;
          }
        }
      }
      img_dst.at<uchar>(j, i) = num / den;
    }
  }
}

void process(int sigma, const char* ims, const char * imd){
  (void)sigma;
  Mat image_src = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << ims << std::endl ;
    return;
	}

  Mat image_dst = image_src.clone();

  nlmeans(image_src, image_dst, sigma);

  imshow(imd, image_dst);
  imwrite(imd, image_dst);
  waitKey(0);
}

void usage (const char *s) {
  std::cerr<<"Usage: "<<s<<" sigma ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int main( int argc, char* argv[] ){
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), argv[2], argv[3]);
  return EXIT_SUCCESS;
}
