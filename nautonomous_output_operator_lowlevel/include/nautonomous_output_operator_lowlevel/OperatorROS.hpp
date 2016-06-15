/*
 * OperatorROS.hpp
 *
 *  Created on: May 24, 2016
 *      Author: zeeuwe01
 */

#ifndef OPERATORROS_HPP_
#define OPERATORROS_HPP_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h"
#include "OperatorPublisher.hpp"

using namespace std;

void propulsionROSCallback(const geometry_msgs::Twist::ConstPtr& twist);
void conveyorROSCallback(const geometry_msgs::Twist::ConstPtr& twist);
void lightingROSCallback(const std_msgs::Bool::ConstPtr& state);

#endif /* OPERATORROS_HPP_ */
