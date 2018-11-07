#include <vector>
#include <morphology.hpp>

using namespace cv;

void
mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar*))
{
  for(int i = 0; i < ims.rows; i++){
    for(int j = 0; j < ims.cols; j++){
      uchar value = ims.at<uchar>(i, j);
      for(int k = 0; k < se.rows; k++){
        for(int l = 0; l < se.cols; l++){
          int i_target = i + k - se.rows / 2;
          int j_target = j + l - se.cols / 2;
          if(se.at<uchar>(k, l)){
            if(
              i_target >= 0 && i_target < ims.rows &&
              j_target >= 0 && j_target < ims.cols
            ){
              pf(ims.at<uchar>(i_target, j_target), &value);
            }
          }
        }
      }
      imd.at<uchar>(i, j) = value;
    }
  }
}

void
maximum(uchar val, uchar* max)
{
  if(val > *max)
    *max = val;
}

void
minimum(uchar val, uchar* min)
{
  if(val < *min)
    *min = val;
}
