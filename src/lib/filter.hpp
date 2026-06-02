#include "opencv2/opencv.hpp"  
#include "vector"

using namespace cv;
using namespace std;

/* Reflect the border of the image to apply the Lee filter on the edge of the image */
void strideImg(Mat &image, Mat &padded_image, int padding){
   copyMakeBorder(image, padded_image, padding, padding, padding, padding, BORDER_REFLECT);
}

template<typename T>
Mat refinedFilter(Mat &image, int window){

  int c = 0;
  Mat debugChannel = Mat::ones(image.rows, image.cols, CV_32F) * 1;
  vector<Mat> debugVec;

  debugVec.push_back(debugChannel);

  
  int padding = window / 2;
  for(int i = padding; i < image.rows - padding; i++){
    for(int j = padding; j < image.cols - padding; j++){
      T pixel = image.at<T>(i, j);
      // image.at<T>(i, j) = 1;
      //image.at<Vec3b>(i, j) *= image.at<Vec3b>(i, j);
      cout << "Row: " << i << " Col: " << j << " ( " << (T)pixel << " ) "<< endl;
    }
  }

  debugVec.push_back(image);
  debugVec.push_back(debugChannel);
  
  Mat debugImg;

  merge(debugVec, debugImg);
  
  return debugImg;
}
