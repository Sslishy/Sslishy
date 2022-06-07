#include <opencv2/aruco.hpp>
#include<opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include"camconcrol.h"
using namespace std;
using namespace cv;
int main()
{
    CamConcrol cc;
    cc.OpemCam();
    cc.CamCapture();
    
    cv::Mat img;
    cc.GetImage(img);
    
    // 加载用于生成标记的字典
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    // 使用默认值初始化检测器参数  
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    // 声明包含检测到的标记角和被拒绝的标记候选的向量  markercorners[0]:左上角；markercorners[1]:右上角； markercorners[2]:左下角； markercorners[3]:右下角；   
    vector<vector<Point2f>> markerCorners, rejectedCandidates;
    // 检测到的标记的id存储在一个向量中  
    vector<int> markerIds;
    cv::imshow("img",img);
    vector<vector<vector<cv::Point3f>>> map;
    vector<cv::Point3f> points;
    
    while (true)
    {
        int key = waitKey(0);
        if (key == 67)
        {   
            cc.CamCapture();
            cc.GetImage(img);
            // 检测图像中的标记
            cv::aruco::detectMarkers(img, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
            cv::aruco::drawDetectedMarkers(img,markerCorners);
            cv::imshow("img",img);
            map = cc.Get2d3dMap();
            cout <<"3Dmark point:" map[markerCorners[0][0].y][markerCorners[0][0].x][0] <<endl;
            points.push_back(map[markerCorners[0][0].y][markerCorners[0][0].x][0]);
            cout <<"2Dmark point:" markerCorners[0][0] <<endl;
        }
        if(key == 27)
        {
            for (size_t i = 0; i < points.size(); i++)
            {
                ofstream ofs;  
                ofs.open("points.txt",ios::out );
                ofs  << points[i] << endl;  //endl用于换行
                ofs.close();
            }
            
        }

    
    }
    
    


}