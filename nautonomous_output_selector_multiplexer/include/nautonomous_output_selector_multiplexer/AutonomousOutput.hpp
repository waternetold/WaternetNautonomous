/*
 * AutonomousInput.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef AUTONOMOUSINPUT_HPP_
#define AUTONOMOUSINPUT_HPP_

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "MessagePriority.h"
#include "OutputMultiplexer.hpp"

void autonomousPropulsionCallback(const geometry_msgs::Twist::ConstPtr& msg);

void autonomousConveyorCallback(const geometry_msgs::Twist::ConstPtr& msg);

void autonomousLightingCallback(const std_msgs::Bool::ConstPtr& msg);


#endif /* AUTONOMOUSINPUT_HPP_ */
