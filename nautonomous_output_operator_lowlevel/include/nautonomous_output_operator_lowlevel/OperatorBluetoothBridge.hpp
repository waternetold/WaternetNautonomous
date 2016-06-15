/*
 * OperatorBluetoothBridge.hpp
 *
 *  Created on: May 10, 2016
 *      Author: zeeuwe01
 */

#ifndef OPERATORBLUETOOTHBRIDGE_HPP_
#define OPERATORBLUETOOTHBRIDGE_HPP_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "mavros_msgs/RCIn.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "string"
#include <stdio.h>
#include <string.h>

#include "OperatorPublisher.hpp"

using namespace std;

extern geometry_msgs::Twist* propulsionMessage;
extern geometry_msgs::Twist* conveyorMessage;
extern std_msgs::Bool* lightingMessage;

extern void check_publishing();

void bluetoothCallback(const std_msgs::String::ConstPtr& msg);

#endif /* OPERATORBLUETOOTHBRIDGE_HPP_ */
