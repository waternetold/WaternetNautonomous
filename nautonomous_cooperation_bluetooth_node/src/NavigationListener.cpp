
#include "ros/ros.h"
#include "../include/nautonomous_cooperation_bluetooth_node/NavigationListener.hpp"

void bluetoothGoalPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
	ROS_INFO("Receive navigation pose message");
	if(!goalPoseStamped){
		goalPoseStamped = new geometry_msgs::PoseStamped();
	}
	goalPoseStamped->header = msg->header;
	goalPoseStamped->pose = msg->pose;

}
