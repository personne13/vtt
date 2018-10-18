#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void compute_at_method(Mat im){
  Vec3b v(32, 32, 32);

  for(int i = 0; i < im.cols; i++){
    for(int j = 0; j < im.rows; j++){
      im.at<Vec3b>(j, i) = 1/64.0 * im.at<Vec3b>(j, i) * 64.0 + v;
    }
  }
}

void compute_iterator_method(Mat im){
  MatIterator_<Vec3b> end = im.end<Vec3b>();
  Vec3b v(32, 32, 32);

  for(MatIterator_<Vec3b> i = im.begin<Vec3b>(); i != end; i++){
    (*i) = 1/64.0 * (*i) * 64 + v;
  }
}

void compute_matrixoperation_method(Mat im){
  Mat V(im.rows, im.cols, CV_8UC3, Scalar(32, 32, 32));

  im = (1/64.0 * im) * 64.0 + V;
}

void compute_pointer_method(Mat im){
  (void)im;
  Vec3b v(32, 32, 32);

  for(int r = 0; r < im.rows; r++) {
      cv::Vec3b* ptr = im.ptr<cv::Vec3b>(r);

      for(int c = 0; c < im.cols; c++) {
          ptr[c] = 1/64.0 * ptr[c] * 64 + v;
        }
  }
}

void
process(const char* imsname)
{
  int t1, t2;
  double exec_time;
  Mat image_src;
  image_src = imread(imsname, CV_LOAD_IMAGE_COLOR);

  if(!image_src.data){
      cout <<  "Could not open image" << imsname << std::endl ;
      return;
  }

  imshow("base", image_src);

  Mat test_mat;

  test_mat = image_src.clone();
  t1 = getTickCount();
  compute_at_method(test_mat);
  t2 = getTickCount();
  exec_time = (t2 - t1) / getTickFrequency();
  cout << "At method: " << exec_time << "s" << std::endl;

  test_mat = image_src.clone();
  t1 = getTickCount();
  compute_iterator_method(test_mat);
  t2 = getTickCount();
  exec_time = (t2 - t1) / getTickFrequency();
  cout << "Iterator method: " << exec_time << "s" << std::endl;

  test_mat = image_src.clone();
  t1 = getTickCount();
  compute_matrixoperation_method(test_mat);
  t2 = getTickCount();
  exec_time = (t2 - t1) / getTickFrequency();
  cout << "Matrix operation method: " << exec_time << "s" << std::endl;

  test_mat = image_src.clone();
  t1 = getTickCount();
  compute_pointer_method(test_mat);
  t2 = getTickCount();
  exec_time = (t2 - t1) / getTickFrequency();
  cout << "Pointer method: " << exec_time << "s" << std::endl;

  waitKey(0);
}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
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
