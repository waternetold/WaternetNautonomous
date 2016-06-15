/*
 * ReceiveActuation.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef RECEIVEACTUATION_HPP_
#define RECEIVEACTUATION_HPP_

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"

#include "CommandActuation.hpp"
#include "SendActuation.hpp"

void propulsionCallback(const geometry_msgs::Twist::ConstPtr& msg);

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void conveyorCallback(const geometry_msgs::Twist::ConstPtr& msg);

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void lightingCallback(const std_msgs::Bool::ConstPtr& msg);

extern geometry_msgs::Twist* propulsion_message;
extern geometry_msgs::Twist* conveyor_message;
extern std_msgs::Bool* lighting_message;


#endif /* RECEIVEACTUATION_HPP_ */
