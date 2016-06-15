/*
 * OutputMultiplexer.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef OUTPUTMULTIPLEXER_HPP_
#define OUTPUTMULTIPLEXER_HPP_



#include "ros/ros.h"
#include "std_msgs/String.h"
#include "string"

#include "AutonomousOutput.hpp"
#include "ManualOutput.hpp"

#include "MessagePriority.h"

using namespace std;

ros::Publisher propulsion_publisher;
ros::Publisher conveyor_publisher;
ros::Publisher lighting_publisher;

void propulsionCallback(const geometry_msgs::Twist::ConstPtr& msg,
		MessagePriority priority);

void conveyorCallback(const geometry_msgs::Twist::ConstPtr& msg,
		MessagePriority priority);

void lightingCallback(const std_msgs::Bool::ConstPtr& msg,
		MessagePriority priority);

class TwistOutputMessage {
public:
	TwistOutputMessage();
	TwistOutputMessage(geometry_msgs::Twist twist, MessagePriority priority);
	void clear();

	geometry_msgs::Twist twist;
	MessagePriority priority;

};

TwistOutputMessage::TwistOutputMessage(){
	clear();
}

TwistOutputMessage::TwistOutputMessage(geometry_msgs::Twist twist, MessagePriority priority){
	this->twist = twist;
	this->priority = priority;
}

void TwistOutputMessage::clear(){
	this->twist = geometry_msgs::Twist();
	this->priority = MessagePriority::MSG_PRIO_LOW;
}

class BoolOutputMessage {
public:
	BoolOutputMessage();
	BoolOutputMessage(bool state, MessagePriority priority);
	void clear();

	std_msgs::Bool state;
	MessagePriority priority;

};

BoolOutputMessage::BoolOutputMessage(){
	clear();
}

BoolOutputMessage::BoolOutputMessage(bool state, MessagePriority priority){
	this->state.data = state;
	this->priority = priority;
}

void BoolOutputMessage::clear(){
	this->state.data = false;
	this->priority = MessagePriority::MSG_PRIO_LOW;
}

TwistOutputMessage* propulsion_message = nullptr;
TwistOutputMessage* conveyor_message = nullptr;
BoolOutputMessage* lighting_message = nullptr;

#endif /* OUTPUTMULTIPLEXER_HPP_ */
