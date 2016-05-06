#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(int argc, char **argv){

	char* imageName = argv[1];
	Mat image;
  image = imread(imageName, 1);

  namedWindow("Image Color", WINDOW_NORMAL);
  imshow("Image Color",image);
  
  waitKey(0);
  
  return 0;

}
