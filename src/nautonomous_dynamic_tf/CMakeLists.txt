cmake_minimum_required(VERSION 2.8.3)
project(nautonomous_dynamic_tf)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES nautonomous_dynamic_tf
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(dynamic_tf src/dynamic_tf.cpp)
target_link_libraries(dynamic_tf ${catkin_LIBRARIES})

