#ifndef OPERATORLISTENER_H_
#define OPERATORLISTENER_H_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h"

geometry_msgs::Twist* propulsionTwist = nullptr;
geometry_msgs::Twist* conveyorTwist = nullptr;
std_msgs::Bool* lightingBool = nullptr;

void bluetoothOperatorPropulsionCallback(const geometry_msgs::Twist::ConstPtr& msg);

void bluetoothOperatorConveyorCallback(const geometry_msgs::Twist::ConstPtr& msg);

void bluetoothOperatorLightingCallback(const std_msgs::Bool::ConstPtr& msg);


#endif /* OPERATORLISTENER */
