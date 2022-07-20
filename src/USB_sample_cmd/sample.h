#if defined(_WIN32)
#include <Windows.h>
#elif defined(linux) || defined(unix)
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif

#include <stdio.h>
#include <iostream>
#include "cmd.h"
#include "camera.h"
#include "display.h"
 #include <ros/ros.h>
 #include <image_transport/image_transport.h>
 #include <cv_bridge/cv_bridge.h>
 #include <sensor_msgs/image_encodings.h>
#include "std_msgs/String.h"
#include <sensor_msgs/Image.h>


#define IR_SAMPLE_VERSION "0.1.2 alpha"

ros::Publisher image_pub;
IruvcHandle_t* iruvc_handle1;

typedef enum {
	DEBUG_PRINT = 0,
	ERROR_PRINT,
	NO_PRINT,
}log_level_t;

//#define USER_FUNCTION_CALLBACK
