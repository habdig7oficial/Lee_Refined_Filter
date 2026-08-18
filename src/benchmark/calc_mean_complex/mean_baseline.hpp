#pragma once

#include "opencv2/opencv.hpp"  


using namespace cv;
using namespace std;
using namespace env;

/* image, image x point, image y point, correspodent window, direction */
/* Bitset Version to benchmark only the true function is in filter.hpp */

/* Unsigned int for benchmark macro compatibility */
template <typename T = double, unsigned int N = 11>
double calc_mean_complex(Mat& image, int tx, int ty, BitSetMask<N>& window, bool is_reverse){
  double sin_complex = 0, cos_real = 0;

  if(is_reverse == NOT_ROTATED){
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){

	T pixel;
	if(window(j, i))
	  pixel = 0;
	else
	  pixel = *(image.ptr<T>(i) + j);

	sin_complex += sin((double) pixel);
	cos_real += cos((double) pixel);
      }
    }
  }
  else{
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){

	T pixel;
	if(window(i, j))
	  pixel = 0;
	else
	  pixel = *(image.ptr<T>(i) + j);

	sin_complex += sin((double) pixel);
	cos_real += cos((double) pixel);
      }
    }
  }

  sin_complex /= N * N;
  cos_real /= N * N;

  return atan2(sin_complex, cos_real);
}

