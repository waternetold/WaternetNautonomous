/*
 * ManualOutput.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef MANUALOUTPUT_HPP_
#define MANUALOUTPUT_HPP_

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "MessagePriority.h"
#include "OutputMultiplexer.hpp"

void manualPropulsionCallback(const geometry_msgs::Twist::ConstPtr& msg);

void manualConveyorCallback(const geometry_msgs::Twist::ConstPtr& msg);

void manualLightingCallback(const std_msgs::Bool::ConstPtr& msg);

bool manualOverride = false;

#endif /* MANUALOUTPUT_HPP_ */
