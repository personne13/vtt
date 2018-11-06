#include <morphology.hpp>

using namespace cv;

void
mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar*))
{
  (void) se;
  (void) ims;
  (void) imd;
  (void) pf;
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
