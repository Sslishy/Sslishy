
#include"OpenCam.h"
OpenCam::OpenCam()
{
}
bool OpenCam::OpenCamera()
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
      
        return false;
    }
    else
    {
          if (x1.Capture() == true) {
    } else {
        std::cout << "RVC X Camera capture failed!" << std::endl;
        return false;
    }
        std::cout << "RVC X Camera is opened!" << std::endl;
         return false;
    }
   
}


OpenCam::~OpenCam()
{
}
