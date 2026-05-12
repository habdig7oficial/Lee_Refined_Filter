#include "iostream"
#include "opencv2/opencv.hpp"  
#include "string.h"

using namespace std;
using namespace cv;

struct config_struct {
  char *image_path;
  char *coherence_path;
  char color_type;
};

int main(int argc, char *argv[]){

  struct config_struct config = {};
  
  for(int i = 0; i < argc; i++){
    if(strcmp(argv[i], "--coherence") == 0)
      config.coherence_path = argv[i + 1];
    
    if(strcmp(argv[i], "--image") == 0)
      config.image_path = argv[i + 1];
 
    if(strcmp(argv[i], "--channels") == 0)
      config.color_type = atoi(argv[i + 1]);
   
  }

  if(strcmp(config.image_path, "") == 0){
    fprintf(stderr, "Image was not provided\n");
    return -1;
  }
  else if(strcmp(config.coherence_path, "") == 0){
    fprintf(stderr, "Coherence file was not provided\n");
    return -1;
  }
  
  Mat image = imread(config.image_path, IMREAD_ANYDEPTH | config.color_type);
  Mat coherence = imread(config.coherence_path, IMREAD_ANYDEPTH | config.color_type );

  Mat padded;
  copyMakeBorder(image, padded, 100, 100, 100, 100, BORDER_REFLECT);

  Mat slice = image(Range(0,100), Range(0,100));
  
  imshow("Original Image", image);
  imshow("Coherence Image", coherence);
  imshow("Reflected Image", padded);
  imshow("Reflected Image", slice);
  waitKey(0);


  //bool saved = imwrite("./output.tiff", padded);

  destroyAllWindows();
  return 0;
}
