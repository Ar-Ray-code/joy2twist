cmake_minimum_required(VERSION 3.5)
project(joy2twist)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

include_directories(
  include/joy2twist
)

add_executable(joy2twist
  src/joy2twist.cpp
)

ament_target_dependencies(joy2twist
  rclcpp
  sensor_msgs
  example_interfaces
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  joy2twist
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()