cmake_minimum_required(VERSION 2.8.3)
project(performance_tests)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
   FILES
   SuperAwesome.msg
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
 )


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(performance_publisher src/performance_publisher.cpp)
target_link_libraries(performance_publisher ${catkin_LIBRARIES})
add_dependencies(performance_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(performance_subscriber src/performance_subscriber.cpp)
target_link_libraries(performance_subscriber ${catkin_LIBRARIES})
add_dependencies(performance_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})