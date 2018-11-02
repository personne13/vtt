#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define t 0.1

void preprocess(int sigma, std::vector<float> &G){
    float den = 2 * sigma * sigma;
    float res = 2 * t;
    int x = 0;

    while(res > t){
      res = exp(-(x * x) / den);
      G.push_back(res);
      x++;
    }
}

int dist_L2(int i, int j, int k, int l){
  return abs(k - i) + abs(l - j);
}

int dist_intensity(int i1, int i2){
  return abs(i1 - i2);
}

void bilateral(Mat &img_src, Mat &img_dst, std::vector<float> &Gg, std::vector<float> &Gs){
  for(int i = 0; i < img_src.cols; i++){
    for(int j = 0; j < img_src.rows; j++){
      float num = 0;
      float den = 0;
      for(int k = i - (int)Gs.size(); k < i + (int)Gs.size(); k++){
        for(int l = j - (int)Gs.size(); l < j + (int)Gs.size(); l++){
          if(k >= 0 && k < img_src.cols &&
             l >= 0 && l < img_src.rows){
              int dist_s = dist_L2(i, j, k, l);
              int dist_i = dist_intensity(img_src.at<uchar>(l, k), img_src.at<uchar>(j, i));

              if(dist_s < (int)Gs.size() && dist_i < (int)Gg.size()){
                float tmp = Gs[dist_s] * Gg[dist_i];
                num += tmp * img_src.at<uchar>(l, k);
                den += tmp;
              }
          }
        }
      }
      img_dst.at<uchar>(j, i) = num / den;
    }
  }
}

void process(int sigma_s, int sigma_g, const char* ims, const char * imd){
  (void)sigma_s;
  (void)sigma_g;
  (void)imd;

  std::vector<float> Gs;
  std::vector<float> Gg;
  Mat image_src = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << ims << std::endl ;
    return;
	}

  Mat image_dst = image_src.clone();
  Mat image_dst_oc = image_src.clone();

  preprocess(sigma_g, Gg);
  preprocess(sigma_s, Gs);

  bilateral(image_src, image_dst, Gg, Gs);
  bilateralFilter(image_src, image_dst_oc, Gg.size(), sigma_g, sigma_s);

  imwrite(imd, image_dst);
  imshow("diff", image_dst - image_dst_oc);
  waitKey(0);
}

void usage (const char *s) {
  std::cerr<<"Usage: "<<s<<" sigma_s sigma_g ims imd\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int main( int argc, char* argv[] ){
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
  return EXIT_SUCCESS;
}
