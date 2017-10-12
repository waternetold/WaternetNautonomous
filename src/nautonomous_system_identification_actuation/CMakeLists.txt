cmake_minimum_required(VERSION 2.8.3)
project(nautonomous_system_identification_actuation)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)


catkin_package(

)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(random_actuation_signals src/random_actuation_signals.cpp)
target_link_libraries(random_actuation_signals ${catkin_LIBRARIES})

