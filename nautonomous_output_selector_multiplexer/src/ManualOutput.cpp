/*
 * ManualInput.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#include "../include/nautonomous_output_selector_multiplexer/OutputMultiplexer.hpp"

void manualPropulsionCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	//ROS_INFO("Manual Propulsion received : linear [%f, %f, %f] and angular [%f, %f, %f]", msg->linear.x, msg->linear.y, msg->linear.z, msg->angular.x, msg->angular.y, msg->angular.z);
	propulsionCallback(msg, MessagePriority::MSG_PRIO_HIGH);
}

void manualConveyorCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	//ROS_INFO("Manual Conveyor received : linear [%f, %f, %f] and angular [%f, %f, %f]", msg->linear.x, msg->linear.y, msg->linear.z, msg->angular.x, msg->angular.y, msg->angular.z);
	conveyorCallback(msg, MessagePriority::MSG_PRIO_HIGH);
}

void manualLightingCallback(const std_msgs::Bool::ConstPtr& msg)
{
	//ROS_INFO("Manual Lighting received: [%d]", msg->data);
	lightingCallback(msg, MessagePriority::MSG_PRIO_HIGH);
}

