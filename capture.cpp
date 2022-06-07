#include </opt/RVC/include/RVC/RVC.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "/opt/RVC/examples/C++/IO/FileIO.h"
#include "/opt/RVC/examples/C++/IO/SavePointMap.h"
#include"CameraControl.h"
using namespace std;
int main(int argc, char *argv[]) {
   cv::Mat image;
   CameraControl cc;
   cc.Getimage();
   cout << image.cols <<endl;
   return 0;
}