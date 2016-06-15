/*
 * OutputMultiplexer.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#include "../include/nautonomous_output_selector_multiplexer/OutputMultiplexer.hpp"

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void propulsionCallback(const geometry_msgs::Twist::ConstPtr& msg,
		MessagePriority priority) {
	//ROS_INFO("Multiplexing Propulsion received : linear [%f, %f, %f] and angular [%f, %f, %f] %d", msg->linear.x, msg->linear.y, msg->linear.z, msg->angular.x, msg->angular.y, msg->angular.z, priority );
	if(!propulsion_message){
		propulsion_message = new TwistOutputMessage();
	}
	//ROS_INFO("priority %d propulsion_message->priority %d ", priority, propulsion_message->priority);
	if (priority <= propulsion_message->priority) {
		std_msgs::String name;
		propulsion_message->twist.angular = msg->angular;
		propulsion_message->twist.linear = msg->linear;
		propulsion_message->priority = priority;
	} else {
		ROS_WARN("incoming message of lower priority %d, ignoring it ...", priority);
	}
}

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void conveyorCallback(const geometry_msgs::Twist::ConstPtr& msg,
		MessagePriority priority) {
	//ROS_INFO("Multiplexing Conveyor received : linear [%f, %f, %f] and angular [%f, %f, %f]", msg->linear.x, msg->linear.y, msg->linear.z, msg->angular.x, msg->angular.y, msg->angular.z);
	if(!conveyor_message){
		conveyor_message = new TwistOutputMessage();
	}
	if (priority <= conveyor_message->priority) {
		conveyor_message->twist.angular = msg->angular;
		conveyor_message->twist.linear = msg->linear;
		conveyor_message->priority = priority;
	} else {
		ROS_WARN("incoming message of lower priority, ignoring it ...");
	}
}

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void lightingCallback(const std_msgs::Bool::ConstPtr& msg,
		MessagePriority priority) {
	//ROS_INFO("Multiplexing Lighting received: [%d]", msg->data);
	if(!lighting_message){
		lighting_message = new BoolOutputMessage();
	}
	if (priority <= lighting_message->priority) {
		lighting_message->state.data = msg->data;
		lighting_message->priority = priority;
	} else {
		ROS_WARN("incoming message of lower priority, ignoring it ...");
	}
}

void publishOutput() {
	std_msgs::String propulsion;

	if(propulsion_message){
		propulsion_publisher.publish(propulsion_message->twist);
		delete propulsion_message;
		propulsion_message = nullptr;
	}
	if(conveyor_message){
		conveyor_publisher.publish(conveyor_message->twist);
		delete conveyor_message;
		conveyor_message = nullptr;
	}
	if(lighting_message){
		lighting_publisher.publish(lighting_message->state);
		delete lighting_message;
		lighting_message = nullptr;
	}

}

int main(int argc, char **argv) {

	ros::init(argc, argv, "output_multiplexer");

	ros::NodeHandle n;

	propulsion_message = nullptr;
	conveyor_message = nullptr;
	lighting_message = nullptr;

	ros::Subscriber manualPropulsionSub = n.subscribe("manual_propulsion", 1000,
			manualPropulsionCallback);
	ros::Subscriber manualConveyorSub = n.subscribe("manual_conveyor", 1000,
			manualConveyorCallback);
	ros::Subscriber manualLightingSub = n.subscribe("manual_lighting", 1000,
			manualLightingCallback);

	ros::Subscriber autonomousPropulsionSub = n.subscribe(
			"autonomous_propulsion", 1000, autonomousPropulsionCallback);
	ros::Subscriber autonomousConveyorSub = n.subscribe("autonomous_conveyor",
			1000, autonomousConveyorCallback);
	ros::Subscriber autonomousLightingSub = n.subscribe("autonomous_lighting",
			1000, autonomousLightingCallback);

	propulsion_publisher = n.advertise<geometry_msgs::Twist>(
			"multiplexed_propulsion", 1000);
	conveyor_publisher = n.advertise<geometry_msgs::Twist>("multiplexed_conveyor",
			1000);
	lighting_publisher = n.advertise<std_msgs::Bool>("multiplexed_lighting",
			1000);

	ros::Rate rate(10);
	int index = 0;
	while (ros::ok()) {
	
		publishOutput();
		index = 0;

		rate.sleep();
		ros::spinOnce();
	}

	ros::spin();

	return 0;
}

