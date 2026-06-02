#include "iostream"
#include "opencv2/opencv.hpp"  
#include "string.h"

using namespace std;
using namespace cv;

struct config_struct {
  char *image_path;
  char *coherence_path;
  char color_type;
  char window;
};


template<typename T>
Mat refinedFilter(Mat &image, int window){
  int padding = window / 2;
  for(int i = padding; i < image.rows - padding; i++){
    for(int j = padding; j < image.cols - padding; j++){
      T pixel = image.at<T>(i, j);
      image.at<T>(i, j) = 1;
      //image.at<Vec3b>(i, j) *= image.at<Vec3b>(i, j);
      cout << "Row: " << i << " Col: " << j << " ( " << (T)pixel << " ) "<< endl;
    }
  }
  return image;
}


int main(int argc, char *argv[]){

  struct config_struct config = {};
  
  for(int i = 0; i < argc; i++){
    if(strcmp(argv[i], "--coherence") == 0)
      config.coherence_path = argv[i + 1];
    
    if(strcmp(argv[i], "--image") == 0)
      config.image_path = argv[i + 1];
 
    if(strcmp(argv[i], "--channels") == 0)
      config.color_type = atoi(argv[i + 1]);

    if(strcmp(argv[i], "--window") == 0)
      config.window = atoi(argv[i + 1]);
  }

  if(strcmp(config.image_path, "") == 0){
    fprintf(stderr, "Image was not provided\n");
    return -1;
  }
  else if(strcmp(config.coherence_path, "") == 0){
    fprintf(stderr, "Coherence file was not provided\n");
    return -1;
  }
  else if(config.window == 0){
    config.window = 11;
  }
  
  Mat image = imread(config.image_path, IMREAD_ANYDEPTH | IMREAD_GRAYSCALE);
  Mat coherence = imread(config.coherence_path, IMREAD_UNCHANGED );

  int padding = config.window / 2;

  cout << "Rows: " << image.rows << " Cols: " << image.cols << " Channels: " << image.channels() << " Depth: " << image.depth() << " Type: " << image.type()<< endl;
  cout << "Window is: " << (int) config.window << " Reflected padded is: " << padding << endl;
  Mat padded_image;
  copyMakeBorder(image, padded_image, padding, padding, padding, padding, BORDER_REFLECT);

  Mat filtered;

  switch(image.depth()){
    case CV_8U:
	filtered = refinedFilter<uchar>(padded_image, config.window);
      break;

    case CV_16U:
      filtered = refinedFilter<ushort>(padded_image, config.window);
      break;
       

    case CV_32F:
	filtered = refinedFilter<float>(padded_image, config.window);
      break;

    default:
      printf("Unsuported Prescision");
      return 1;
  }

  imshow("Original Image", image);
  imshow("Coherence Image", coherence);
  imshow("Reflected Image", padded_image);
  imshow("Filtered Image", filtered);
  waitKey(0);


  bool saved = imwrite("./output.tiff", filtered);

  destroyAllWindows();
  return 0;
}
