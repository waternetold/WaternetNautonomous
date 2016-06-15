/*
 * OperatorLowLevel.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef OPERATORLOWLEVEL_HPP_
#define OPERATORLOWLEVEL_HPP_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "mavros_msgs/RCIn.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "string"
#include <stdio.h>
#include <string.h>

#include "OperatorBluetoothBridge.hpp"
#include "OperatorRCBridge.hpp"
#include "OperatorROS.hpp"

#define LIGHTING_THRESHOLD 600

using namespace std;

ros::Subscriber propulsionSub;
ros::Subscriber conveyorSub;
ros::Subscriber lightingSub;

ros::Publisher propulsionPub;
ros::Publisher conveyorPub;
ros::Publisher lightingPub;

geometry_msgs::Twist* propulsionMessage = nullptr;
geometry_msgs::Twist* conveyorMessage = nullptr;
std_msgs::Bool* lightingMessage = nullptr;

void publish_propulsion();
void publish_conveyor();
void publish_lighting();

void check_publishing();


#endif /* OPERATORLOWLEVEL_HPP_ */
