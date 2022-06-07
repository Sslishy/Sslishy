#include </opt/RVC/include/RVC/RVC.h>
#include <iostream>
#include "/opt/RVC/examples/C++/IO/FileIO.h"
#include "/opt/RVC/examples/C++/IO/SavePointMap.h"
class OpenCam
{
protected:
    RVC::X1 x1;
public:
    OpenCam(/* args */);
    bool OpenCamera();
    ~OpenCam();
};

