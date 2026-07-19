#include "opencv2/opencv.hpp"  
#include "vector"

#include "format"

#include "cmath"
#include "gierull.hpp"
#include "magic_points.hpp"
#include "gsl/gsl_integration.h"
#include "complex"

#define TOLERANCE 1e-9
#define MAX_ITERATIONS 9'999

using namespace cv;
using namespace std;


/* Reflect the border of the image to apply the Lee filter on the edge of the image */
void strideImg(Mat &image, Mat &padded_image, int padding){
   copyMakeBorder(image, padded_image, padding, padding, padding, padding, BORDER_REFLECT);
}

gsl_integration_workspace *w = gsl_integration_workspace_alloc(1'000);
tuple<double, double> integrate(gsl_function *F, double limit){
  double target_val, err;
  gsl_integration_qags(F, -limit, limit, 0, 1e-7, 1'000, w, &target_val, &err);
  return {target_val, err};
}



tuple<double, double, int> match_area_x(gsl_function *F, double lower_limit, double upper_limit, double xi, int max_iter = MAX_ITERATIONS){
  /* Integral */
  /* 
  Search the point where integral(x) = 0.9, 
  the original R code uses linear search witch uses more (310 for simulated img) checks,
  the revised C++ code uses binary serch (bissection method) that uses far less
  */

  double estimated_val, err;
  double high = upper_limit, low = lower_limit, mid;

  int i;
  for(i = 0; i < max_iter; (estimated_val < xi)? (low = mid) : (high = mid), i++){
    mid = low + (high - low) / 2;
    tuple<double, double> t = integrate(F, mid);
    estimated_val = get<0>(t);
    err = get<1>(t);

    if(isinf(estimated_val) || isnan(estimated_val)){
      string msg = std::format("Integrated {} value is invalid! ", estimated_val);
      throw runtime_error(msg);
    }

    if(abs(estimated_val - xi) < TOLERANCE){
        cout << "Found new x: " << mid << endl; 
        break;
    }

    cout << i << ") x: " << mid << ", integral: " << estimated_val << " high: " << high << " low: " << low << " mid: " << mid << endl; 

  }

  if(i == max_iter){
    cout << "MAX Iterations: Value will not be exact, MAX_ITERATIONS = " << max_iter << endl;
  }
  return {mid, estimated_val, i};
}

/* image, image x point, image y point, correspodent window, direction */
template <typename T, size_t N>
double calc_mean_complex(Mat& image, int tx, int ty, MagicPoints<N>& window, bool is_reverse){
  double sin_complex = 0, cos_real = 0;
  auto lambda = [&image, &tx, &ty, &window, &sin_complex, &cos_real](char rx, char ry, bool scope){
        /* Make the absolut points for x and y take the value from image via pointer and cast it to complex */
        T pixel (*(image.ptr<T>(ty - ry) + (tx + rx)));

        sin_complex += sin((double)pixel);
        cos_real += cos((double) pixel);
  };

  if(is_reverse == NOT_ROTATED)
    window.traverse(lambda);
  else 
    window.traverse_inverse(lambda);

  // the cos(0) on the null cels makes 0 that can be decuced without passing
  cos_real += window.unused() * cos(0);

  /* Mean of sin and cos */
  sin_complex /= window.get_area();
  cos_real /= window.get_area();

  double mean = atan2(sin_complex, cos_real);
 
  cout << "Final mean: " << mean << endl;


  return mean;
}

template<typename T>
Mat refinedFilter(Mat &image, int window, int type = CV_32F, double eth = 0.01, double xi = 0.9, double lower_limit = -numbers::pi, double upper_limit = numbers::pi, int max_iter = MAX_ITERATIONS){

  /* Check if window is inside image  */
  int padding = window / 2;

  /* Debug Layer */
  Mat debugImg;
  Mat debugChannel = Mat::ones(image.rows, image.cols, type);
  vector<Mat> debugVec;

  T left, right, top, down, center;
  
  Mat aux = Mat::ones(image.rows, image.cols, type);

  cout << image.rows << " " << image.cols << " " << (image.rows - 2 * padding) * (image.cols - 2 * padding) << " " << padding << endl;

  /* Equation */

  gierull::Param gsl_params = {
    .r = 0.7,
    .theta = 0.0,
    .L = 16
  };

  
  gsl_function F;
  F.function = &gierull::gierull;
  F.params = (void *)&gsl_params;


  auto [res, aprox, iter] = match_area_x(&F, lower_limit, upper_limit, xi, MAX_ITERATIONS);

  cout << "Increments: " << iter << endl;
  cout << "psi_epsilon: " << res << " integral " << aprox << endl;
  
  
  debugVec.push_back(debugChannel);
  debugVec.push_back(image);
  debugVec.push_back(debugChannel);
  merge(debugVec, debugImg);

  calc_mean_complex<T>(image, padding, padding, window0, true);

  return debugImg;
  /*
  for(auto window : all_windows){
      cout << window << endl;

      double acc;

      window.traverse_inverse([&acc, &image, padding](char rx, char ry, bool scope){
        cout << "rx: " << (int)rx << " ry: " << (int)ry << endl; //<< " x: " << x << " y: " << y << " tx: " << x - rx << " ty: " << y - ry << " acc: " << endl;
        //cout << image.ptr<T>(padding - ry) << endl;
        acc++;
      });

      break;
  }*/


  /* Main Loop */
  for(int i = padding; i < image.rows - padding; i++){
    for(int j = padding; j < image.cols - padding; j++){
      T pixel = image.at<T>(i, j);
      
      left = debugChannel.at<T>(i - padding, j);
      right = debugChannel.at<T>(i + padding, j);
      top = debugChannel.at<T>(i, j - padding);
      down = debugChannel.at<T>(i, j + padding);
      center = debugChannel.at<T>(i, j);

      debugChannel.at<T>(i - padding, j) = 
	debugChannel.at<T>(i + padding, j) = 
	debugChannel.at<T>(i, j - padding) = 
	debugChannel.at<T>(i, j + padding) =
	debugChannel.at<T>(i, j) = 0;

      
      debugVec.push_back(debugChannel);
      debugVec.push_back(image);
      debugVec.push_back(debugChannel);
      
      merge(debugVec, debugImg);
      imshow("Making sliding window", debugImg);
      waitKey(1);

      debugChannel.at<T>(i - padding, j) = left;
      debugChannel.at<T>(i + padding, j) = right;
      debugChannel.at<T>(i, j - padding) = top;
      debugChannel.at<T>(i, j + padding) = down;
      debugChannel.at<T>(i, j) = center;

      debugVec.clear();

      T total = 0;
      for(int wi = i - padding; wi < i + padding; wi++){
        for(int wj = j - padding; wj < j + padding; wj++){
          total += image.at<T>(wi, wi);
          cout << "\t (" << wi << " ," << wj << ") =" << total << " "  << image.at<T>(i - padding, j) << endl;
        }
      }

      T mean = (total / window);
      
      cout << "Sum: " << total << ", Avg: " << mean << endl;
      
      //image.at<Vec3b>(i, j) *= image.at<Vec3b>(i, j);
      cout << "Row: " << i << " Col: " << j << " ( " << (T)pixel << " ) "<< endl;
    }
  }
  
    debugVec.push_back(debugChannel);
    debugVec.push_back(image);
    debugVec.push_back(debugChannel);
    merge(debugVec, debugImg);

  gsl_integration_workspace_free(w);
  return debugImg;
}

