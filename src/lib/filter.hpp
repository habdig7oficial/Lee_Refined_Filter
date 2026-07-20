#include "opencv2/opencv.hpp"  


#include "format"

#include "cmath"
#include "gierull.hpp"
#include "magic_points.hpp"
#include "gsl/gsl_integration.h"
#include "complex"

#include "optimization.hpp"

#define TOLERANCE 1e-9
#define MAX_ITERATIONS 9'999

using namespace cv;
using namespace std;
using namespace env;


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



tuple<double, double, int> match_area_x(gsl_function *F, double lower_limit, double upper_limit, double xi, double eth = 0.01, int max_iter = MAX_ITERATIONS){
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

    if constexpr(dev_mode)
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

template<typename T,size_t N>
constexpr array<T, N> dist(){
    array<T, N> arr;

    int half = N / 2;
    for(int i = 0; i < N; i++){
      T res = 1 / sqrt(pow((i + 1) - half, 2) + pow((i + 1) - half, 2));
      
      if(isinf(res))
        arr[i] = 0;
      else 
        arr[i] = res;
    }

    return arr;
}


template<typename T, size_t N>
constexpr T adjust_angle(array<T, N> norm, T ng){
    array<T, N> arr;

    array<T,N> sin_arr = norm;
    array<T,N> cos_arr = norm;

    cout << "Ng: " << ng << endl;

    for(int i = 0; i < N; i++){
      sin_arr[i] *= sin(ng);
      //cout << "sin: " << sin_arr[i] << endl;
    }
      
    
    for(int i = 0; i < N; i++){
      cos_arr[i] *= cos(ng);
      //cout << "cos: " << cos_arr[i] << endl;
    }
      

    return atan2(sum(sin_arr), sum(cos_arr));
}

template<typename T, size_t N, size_t M>
constexpr array<T, M> adjust_angles(array<T, N> dist, array<T, M> angles){
    array<T, M> new_arr;
    array<T, N> norm = normalize(dist);

    for(int i = 0; i < M; i++)
      new_arr[i] = adjust_angle(norm, angles[i]);
    
    return new_arr;
}

template<typename T, size_t N, size_t M>
constexpr array<array<T, M>, M> diff(array<T, N> arr, array<T, M> angles){
  array<array<T, M>, M> new_arr;
  array<T, M> angles_base = adjust_angles(arr, angles);

  for(int i = 0; i < M; i++)
    for(int j = 0; j < M; j++)
      new_arr[i][j] = angles_base[j] - angles[i];
  

  return new_arr;
}


template<typename T>
Mat refinedFilter(Mat &image, int window, int type = CV_32F, double eth = 0.01, double xi = 0.9, double lower_limit = -numbers::pi, double upper_limit = numbers::pi, int max_iter = MAX_ITERATIONS){

  /* Check if window is inside image  */
  int padding = window / 2;

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

  /* Main Loop */
  for(int j = padding; j < image.cols - padding; j++){
    for(int i = padding; i < image.rows - padding; i++){
      double max_mean = 0;
      double select_angle;
      int select_win;

      apply([&max_mean, &image, i, j, &select_win, &select_angle](auto&&... win){
        double aux ;
          ((
            aux = calc_mean_complex<double>(image, i, j, win, NOT_ROTATED),
            (void)[aux, &win, &max_mean, &select_win, &select_angle](){
              if(abs(aux) > max_mean){
                max_mean = aux;
                select_win = win.get_win_num();
                select_angle = win.angle();
              }
              if constexpr(dev_mode)
                cout << win.get_win_num() << ") " << aux << endl;
            }()
          ), ...);
      }, all_windows);

      apply([&max_mean, &image, i, j, &select_win, &select_angle](auto&&... win){
          double aux;
          ((
            aux = calc_mean_complex<double>(image, i, j, win, ROTATED),
            (void)[aux, &win, &max_mean, &select_win, &select_angle](){
              if(abs(aux) > max_mean){
                max_mean = aux;
                select_win = win.get_mirror_num();
                select_angle = win.angle_inverse();
              }
              if constexpr(dev_mode)
                cout << win.get_mirror_num() << ") " << aux << endl;
            }()
          ), ...);
      }, all_windows);

      cout << "Max Mean: " << max_mean << endl;
      cout << "Select win: " << select_win << endl;
      cout << "Angle win: " << select_angle << endl;

      if(max_mean < eth){
        cout << "Is not smooth enought " << endl;
      }
      else 
        cout << "Smooth!" << endl;
    }
  }


  constexpr size_t len = DIMENSION + 2;
  constexpr size_t nglen = 2 * (DIMENSION - 1);

  array<double, nglen> fi = adjust_angles(dist<double, len>(), angles);

  for(int i = 0; i < nglen; i++)
    cout << i << " " << fi[i] << endl;


  array<array<double, nglen>, nglen> test = diff(dist<double, len>(), angles);

  cout << " ==== " << endl;
  for(int i = 0; i < nglen; i++){
      for(int j = 0; j < nglen; j++)
        cout << i << ","  << j << ") " << test[i][j] << endl;

      cout << endl;
  }

  gsl_integration_workspace_free(w);

  return image;
}

