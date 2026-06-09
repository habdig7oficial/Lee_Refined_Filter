#include "iostream"
#include "string.h"
#include "lib/filter.hpp"

using namespace std;

struct config_struct {
  char *image_path;
  char *coherence_path;
  char color_type;
  char window;
};


int main(int argc, char *argv[]){

  /* Set prescision for the whole program  */
  cout << fixed << setprecision(15); 

  /* args  */
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

  /* Equation */
  
  cout << "Gierull Test:" << endl;

  gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);

  double res, err;
  gierull::Param gsl_params = {
    .r = 0.7,
    .theta = 0.0,
    .L = 16
  };

  

  
  /* Image manipulation */
  
  Mat image = imread(config.image_path, IMREAD_ANYDEPTH | IMREAD_GRAYSCALE);
  Mat coherence = imread(config.coherence_path, IMREAD_UNCHANGED );

  int padding = config.window / 2;

  cout << "Rows: " << image.rows << " Cols: " << image.cols << " Channels: " << image.channels() << " Depth: " << image.depth() << " Type: " << image.type()<< endl;
  cout << "Window is: " << (int) config.window << " Reflected padded is: " << padding << endl;

  Mat padded_image;
  strideImg(image, padded_image, padding);

  Mat filtered;

  switch(image.depth()){
    case CV_8U:
      filtered = refinedFilter<uchar>(padded_image, config.window, CV_8U);
      break;

    case CV_16U:
      filtered = refinedFilter<ushort>(padded_image, config.window, CV_16U);
      break;
       

    case CV_32F:
      filtered = refinedFilter<float>(padded_image, config.window, CV_32F);
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
