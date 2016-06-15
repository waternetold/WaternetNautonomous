#ifndef NAVIGATIONLISTENER_H_
#define NAVIGATIONLISTENER_H_

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"

geometry_msgs::PoseStamped* goalPoseStamped = nullptr;

void bluetoothGoalPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);

#endif /* NAVIGATIONLISTENER */
