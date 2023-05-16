cmake_minimum_required(VERSION 3.0.2)
project(exercise_four)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  actionlib_msgs
  actionlib
  dynamic_reconfigure
  tf2
  tf2_ros
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

## Generate actions in the 'action' folder
##add_action_files(
##  FILES
##  PickupPlace.action
##)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs
  actionlib_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

##generate_dynamic_reconfigure_options(
##    cfg/PubMarker.cfg
##)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES advance_demo
#  CATKIN_DEPENDS geometry_msgs roscpp rospy
#  DEPENDS system_lib
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

# Declare a C++ executable
#add_executable(action_server src/action_server.cpp)
# Specify libraries to link a library or executable target against
#target_link_libraries(action_server ${catkin_LIBRARIES})
# Add cmake target dependencies of the executable
#add_dependencies(action_server ${PROJECT_NAME}_generate_messages_cpp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})



add_executable(tf_broadcaster src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})
add_dependencies(tf_broadcaster ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})



add_executable(tf_listener src/tf_listener.cpp)
target_link_libraries(tf_listener ${catkin_LIBRARIES})
add_dependencies(tf_listener ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})



# Mark executable scripts (Python etc.) for installation
#catkin_install_python(PROGRAMS
#  scripts/action_server.py scripts/action_client.py scripts/tf_pub.py scripts/tf_listen.py
#  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)
