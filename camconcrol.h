#ifndef CAMCONCROL_H
#define CAMCONCROL_H
#include<iostream>
#include <opencv2/opencv.hpp>
#include"MyCloud.h"
#include<pcl/visualization/pcl_visualizer.h>
#include </opt/RVC/include/RVC/RVC.h>
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
using namespace std;
class CamConcrol
{
public:
    CamConcrol();
    MyCloud GetPointCloud();
    void OpemCam();
    void CamCapture();
    void CloseCam();
    const inline void GetImage(cv::Mat image)
    {
        image = m_image.clone();
    }
     vector<vector<vector<cv::Point3f>>> Get2d3dMap();
private:
    int id = 0;
    RVC::X1 x1;
    vector<vector<vector<cv::Point3f>>> Aligen2D3DMap;
    cv::Mat m_image;

};

#endif // CAMCONCROL_H
