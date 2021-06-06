cmake_minimum_required(VERSION 3.0.2)
project(joy2twist)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  geometry_msgs
)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include/joy2twist/
)

catkin_package()

add_executable(joy2twist src/joy2twist.cpp)
target_link_libraries(joy2twist ${catkin_LIBRARIES})

add_executable(twist2int32 src/twist2int32.cpp)
target_link_libraries(twist2int32 ${catkin_LIBRARIES})
