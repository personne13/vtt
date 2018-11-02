#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void median_filter(Mat &image_src, Mat &image_dst, int r){
  (void)image_src;
  (void)image_dst;
  (void)r;
  int nb_neighbors = 0;
  std::vector<uchar> neighbors((2 * r + 1) * (2 * r + 1));

  for(int i = 0; i < image_src.cols; i++){
    for(int j = 0; j < image_src.rows; j++){
      nb_neighbors = 0;
      for(int k = i - r; k <= i + r; k++){
        for(int l = j - r; l <= j + r; l++){
          if(k >= 0 && k < image_src.cols &&
             l >= 0 && l < image_src.rows){
            neighbors[nb_neighbors] = image_src.at<uchar>(l, k);
            nb_neighbors++;
          }
        }
      }
      sort (neighbors.begin(), neighbors.begin() + (nb_neighbors));
      uchar med = neighbors[(nb_neighbors - 1) / 2];

      image_dst.at<uchar>(j, i) = med;
    }
  }
}

void process(int r, const char* ims, const char * imd){
  (void)r;
  (void)imd;

  Mat image_src = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image_src.data){
    cout <<  "Could not open file: " << ims << std::endl ;
    return;
	}

  Mat image_dst = image_src.clone();
  Mat image_dst_oc = image_src.clone();

  median_filter(image_src, image_dst, r);

  imwrite(imd, image_dst);
  medianBlur(image_src, image_dst_oc, 2 * r + 1);

  imshow("diff", image_dst - image_dst_oc);

  waitKey(0);
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
