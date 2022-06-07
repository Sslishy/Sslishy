#include "camconcrol.h"
using namespace std;
CamConcrol::CamConcrol()
{
   std::cout << "hello" << std::endl;
}
void CamConcrol::OpemCam()
{
    RVC::SystemInit();
        // Scan all GigE RVC X Camera devices.
        RVC::Device devices[10];
        size_t actual_size = 0;
        SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::GigE);

        // Find whether any RVC X Camera is connected or not.
        if (actual_size == 0) {
            std::cout << "Can not find any GigE RVC X Camera!" << std::endl;

        }
        // Create a RVC X Camera and choose use left side camera.
        x1 = RVC::X1::Create(devices[0], RVC::CameraID_Right);
        // Open RVC X Camera.

        x1.Open();
        // Test RVC X Camera is opened or not.
        if (!x1.IsOpen()) {
            std::cout << "RVC X Camera is not opened!" << std::endl;
            RVC::X1::Destroy(x1);
            RVC::SystemShutdown();
        }else
        {
            std::cout << "RVC X camera is turned on!" << std::endl;
        }
}
void CamConcrol::CamCapture()
{
    RVC::X1::CaptureOptions cap_opt;
       cap_opt.exposure_time_2d = 100;
       cap_opt.gain_2d = 5;
       // Capture a point map and a image with default setting.
       if (x1.Capture(cap_opt) == true) {
          cout << "RVC X Camera capture successful" <<endl;
       } else {
           std::cout << "RVC X Camera capture failed!" << std::endl;

       }
       RVC::Image img = x1.GetImage();
       RVC::PointMap pm = x1.GetPointMap();
       const size_t img_w = img.GetSize().width, img_h = img.GetSize().height;
       cv::Mat image;
       this->Aligen2D3DMap.resize(img_h);
       const double *xyz;
       image.create(img_h,img_w,CV_8UC3);
       const unsigned char *img_data;
       bool is_color = img.GetType() == RVC::ImageType::Mono8 ? false : true;
           for (size_t r = 0; r < img_h; r++) {
               this->Aligen2D3DMap[r].resize(img_w);
               for (size_t c = 0; c < img_w; c++) {
                   img_data = img.GetDataPtr() + (r * img_w + c) * 3;
                   xyz = pm.GetPointDataPtr() + (r * img_w + c) * 3;
                   Aligen2D3DMap[r][c].push_back(cv::Point3f(xyz[0],xyz[1],xyz[2]));
                   image.at<cv::Vec3b>(r,c)[0] = img_data[0];
                   image.at<cv::Vec3b>(r,c)[1] = img_data[1];
                   image.at<cv::Vec3b>(r,c)[2] = img_data[2];
                   //cout <<  image.at<cv::Vec3d>(r,c) <<endl;
               }
           }
      this->m_image = image.clone();
}
vector<vector<vector<cv::Point3f>>> CamConcrol::Get2d3dMap()
{
    return Aligen2D3DMap;
}
MyCloud CamConcrol::GetPointCloud()
{
  MyCloud myCloud;

  for (size_t i = 0; i < this->Aligen2D3DMap.size(); i++)
        {
            for (size_t j = 0; j < this->Aligen2D3DMap[i].size(); j++)
            {

               myCloud.cloud->points.push_back(pcl::PointXYZRGBA(this->Aligen2D3DMap[i][j][0].x,this->Aligen2D3DMap[i][j][0].y,this->Aligen2D3DMap[i][j][0].z
                       ,m_image.at<cv::Vec3b>(i,j)[0],m_image.at<cv::Vec3b>(i,j)[1],m_image.at<cv::Vec3b>(i,j)[2],0));
            }
         }

  myCloud.cloudId = id;
  id= id +1;
  return myCloud;
}
