/*
 * CommandActuation.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef COMMANDACTUATION_HPP_
#define COMMANDACTUATION_HPP_

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"

#include <sstream>

#include "ReceiveActuation.hpp"
#include "SendActuation.hpp"
#include "Serial.hpp"

geometry_msgs::Twist* propulsion_message = nullptr;
geometry_msgs::Twist* conveyor_message = nullptr;
std_msgs::Bool* lighting_message = nullptr;


#endif /* COMMANDACTUATION_HPP_ */
