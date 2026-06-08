#include "opencv2/opencv.hpp"  
#include "vector"

using namespace cv;
using namespace std;


/* Reflect the border of the image to apply the Lee filter on the edge of the image */
void strideImg(Mat &image, Mat &padded_image, int padding){
   copyMakeBorder(image, padded_image, padding, padding, padding, padding, BORDER_REFLECT);
}

template<typename T>
Mat refinedFilter(Mat &image, int window, int type = CV_32F){

  Mat debugImg;
  Mat debugChannel = Mat::ones(image.rows, image.cols, type);
  vector<Mat> debugVec;

  T left, right, top, down, center;
  
  Mat aux = Mat::ones(image.rows, image.cols, type);


  /* Check if window is inside image  */
  int padding = window / 2;
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

  return debugImg;
}

