/*
 * OperatorROS.cpp
 *
 *  Created on: May 24, 2016
 *      Author: zeeuwe01
 */

#include "../include/nautonomous_output_operator_lowlevel/OperatorROS.hpp"

void propulsionROSCallback(const geometry_msgs::Twist::ConstPtr& twist) {
	if(!propulsionMessage){
		propulsionMessage = new geometry_msgs::Twist();
	}
	propulsionMessage->linear = twist->linear;
	propulsionMessage->angular = twist->angular;
	check_publishing();
}
void conveyorROSCallback(const geometry_msgs::Twist::ConstPtr& twist) {
	if(!conveyorMessage){
		conveyorMessage = new geometry_msgs::Twist();
	}
	conveyorMessage->linear = twist->linear;
	conveyorMessage->angular = twist->angular;
	check_publishing();
}
void lightingROSCallback(const std_msgs::Bool::ConstPtr& state) {
	if(!lightingMessage){
		lightingMessage = new std_msgs::Bool();
	}
	lightingMessage->data = state->data;
	check_publishing();
}


