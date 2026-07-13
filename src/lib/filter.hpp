#include "opencv2/opencv.hpp"  
#include "vector"


#include "gierull.hpp"
#include "gsl/gsl_integration.h"

#define TOLERANCE 0.001

using namespace cv;
using namespace std;


/* Reflect the border of the image to apply the Lee filter on the edge of the image */
void strideImg(Mat &image, Mat &padded_image, int padding){
   copyMakeBorder(image, padded_image, padding, padding, padding, padding, BORDER_REFLECT);
}

gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
int integrate(gsl_function *F, double limit, double *target_val, double *err){
  return gsl_integration_qags(F, -limit, limit, 0, 1e-7, 1000, w, target_val, err);
}




template<typename T>
Mat refinedFilter(Mat &image, int window, int type = CV_32F, double eth = 0.01, double xi = 0.9, double lower_limit = -numbers::pi, double upper_limit = numbers::pi){

  /* Check if window is inside image  */
  int padding = window / 2;

  /* Debug Layer */
  Mat debugImg;
  Mat debugChannel = Mat::ones(image.rows, image.cols, type);
  vector<Mat> debugVec;

  T left, right, top, down, center;
  
  Mat aux = Mat::ones(image.rows, image.cols, type);

  cout << image.rows << " " << image.cols << " " << (image.rows - 2 * padding) * (image.cols - 2 * padding) << " " << padding << endl;

  double psi_xi = (-lower_limit + upper_limit) / 2;
  double estimated_val, err;

  cout << "psi_xi " << psi_xi << endl;

  /* Equation */

  gierull::Param gsl_params = {
    .r = 0.7,
    .theta = 0.0,
    .L = 16
  };

  
  gsl_function F;
  F.function = &gierull::gierull;
  F.params = (void *)&gsl_params;

  /*
  cout << "Gierull Test:" << endl;
  //cout << gierull::gierull(2.5, (void *) &gsl_params);
  cout << "Integration Res: " << estimated_val << " Error: " << err << endl;

  cout << "---------------------------" << endl;
  */

  integrate(&F, psi_xi, &estimated_val, &err);
  cout << "First estimated value: " << estimated_val << endl;



  for(int j = padding; j < image.cols - padding; j++){
    for(int i = padding; i < image.rows - padding; i++){
        T pixel = image.at<T>(i, j);
        //gsl_integration_qags(&F, -pixel, pixel, 0, 1e-7, 1000, w, &estimated_val, &err);

        integrate(&F, psi_xi, &estimated_val, &err);
        double s = abs(estimated_val - xi);

              
        cout << "Pixel " << pixel << " Val - xi: " << s << " Estimated Val:  " << estimated_val << endl;
        
        if(s < TOLERANCE){
          psi_xi = pixel;
          cout << "NEW PSI_XI: " << psi_xi << endl;

          debugChannel.at<T>(i, j) = 0;
          break;
        }
      }
    }
    

  debugVec.push_back(debugChannel);
  debugVec.push_back(image);
  debugVec.push_back(debugChannel);
  merge(debugVec, debugImg);

  return debugImg;

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
  /*
    debugVec.push_back(debugChannel);
    debugVec.push_back(image);
    debugVec.push_back(debugChannel);
    merge(debugVec, debugImg);*/

  gsl_integration_workspace_free(w);
  return debugImg;
}

