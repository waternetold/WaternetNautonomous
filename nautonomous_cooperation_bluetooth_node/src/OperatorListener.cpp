
#include "ros/ros.h"
#include "../include/nautonomous_cooperation_bluetooth_node/OperatorListener.hpp"

void bluetoothOperatorPropulsionCallback(const geometry_msgs::Twist::ConstPtr& msg){
	ROS_INFO("Receive propulsion twist message");
	if(!propulsionTwist){
		propulsionTwist = new geometry_msgs::Twist();
	}
	propulsionTwist->angular = msg->angular;
	propulsionTwist->linear = msg->linear;
}

void bluetoothOperatorConveyorCallback(const geometry_msgs::Twist::ConstPtr& msg){
	ROS_INFO("Receive conveyor twist message");
	if(!conveyorTwist){
		conveyorTwist = new geometry_msgs::Twist();
	}
	conveyorTwist->angular = msg->angular;
	conveyorTwist->linear = msg->linear;
}

void bluetoothOperatorLightingCallback(const std_msgs::Bool::ConstPtr& msg){
	ROS_INFO("Receive lighting bool message");
	if(!lightingBool){
		lightingBool = new std_msgs::Bool();
	}
	lightingBool->data = msg->data;
}
