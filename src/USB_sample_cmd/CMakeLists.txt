cmake_minimum_required(VERSION 2.8.3)
project(usb_sample_cmd)

set(SRC_LIST
	camera.cpp
	cmd.cpp
	data.cpp
	display.cpp
	sample.cpp	
)

find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  roscpp
  rospy
  rosconsole
  std_msgs
  image_transport
  cv_bridge
  )

#find_package(Eigen3 REQUIRED)
# find_package(PCL REQUIRED)
# find_package(OpenCV REQUIRED)

include_directories(
    include
	${catkin_INCLUDE_DIRS} 
#	${EIGEN3_INCLUDE_DIR}
    ./libir_sample/opencv2
    ./libs
    ./
	)

catkin_package(
  CATKIN_DEPENDS roscpp rospy rosconsole std_msgs cv_bridge image_transport sensor_msgs
  DEPENDS OpenCV
  INCLUDE_DIRS include
)

link_directories(./libs)

add_executable(sample ${SRC_LIST})
target_link_libraries(sample
    ${catkin_LIBRARIES}
    iruvc
    ircmd
    iri2c
    irprocess
    irparse
    pthread

#opencv related
    opencv_highgui
    opencv_imgcodecs
    opencv_imgproc 
    opencv_core
)