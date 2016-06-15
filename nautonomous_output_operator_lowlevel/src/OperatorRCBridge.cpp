/*
 * OperatorRCBridge.cpp
 *
 *  Created on: May 10, 2016
 *      Author: zeeuwe01
 */
#include "../include/nautonomous_output_operator_lowlevel/OperatorRCBridge.hpp"

void rcCallback(const mavros_msgs::RCIn::ConstPtr& msg) {
    //ROS_INFO("received mavros");
	std::vector<uint16_t> channel = msg->channels;

	bool takeover = false;
	if(channel[CHANNEL_TAKEOVER] > CHANNEL_MAX_THRESHOLD){
		takeover = true;
	} else if(channel[CHANNEL_TAKEOVER] < CHANNEL_MIN_THRESHOLD){
		takeover = false;
	}

	bool propulsionActive = (channel[CHANNEL_DIFMOTOR_PROPULSION] > CHANNEL_MAX_THRESHOLD || channel[CHANNEL_DIFMOTOR_PROPULSION] < CHANNEL_MIN_THRESHOLD) ||
								(channel[CHANNEL_DIFMOTOR_STEERING] > CHANNEL_MAX_THRESHOLD || channel[CHANNEL_DIFMOTOR_STEERING] < CHANNEL_MIN_THRESHOLD);
	bool conveyorActive = (channel[CHANNEL_CONVEYOR_ACTIVATION] > CHANNEL_MAX_THRESHOLD || channel[CHANNEL_CONVEYOR_ACTIVATION] < CHANNEL_MIN_THRESHOLD);

	if(takeover){

		float propulsion = 0.0;
		if(channel[CHANNEL_DIFMOTOR_PROPULSION] > CHANNEL_MAX_THRESHOLD){
			if (channel[CHANNEL_DIFMOTOR_PROPULSION] > CHANNEL_DIFMOTOR_PROPULSION_MAX){
				propulsion = 1.0;
			} else {
				propulsion = ((float)channel[CHANNEL_DIFMOTOR_PROPULSION]-CHANNEL_MEDIAN) / ((float)CHANNEL_DIFMOTOR_PROPULSION_POSITIVE_RANGE);
			}
		} else if(channel[CHANNEL_DIFMOTOR_PROPULSION] < CHANNEL_MIN_THRESHOLD){
			if (channel[CHANNEL_DIFMOTOR_PROPULSION] < CHANNEL_DIFMOTOR_PROPULSION_MIN){
				propulsion = -1.0;
			} else {
				propulsion = ((float)channel[CHANNEL_DIFMOTOR_PROPULSION]-CHANNEL_MEDIAN) / ((float)CHANNEL_DIFMOTOR_PROPULSION_NEGATIVE_RANGE);
			}
		}
		if(propulsion != 0.0 || takeover){
			if(!propulsionMessage){
				propulsionMessage = new geometry_msgs::Twist();
			}
			propulsionMessage->linear.x = propulsion;
		}

		float steering = 0.0;
		if(channel[CHANNEL_DIFMOTOR_STEERING] > CHANNEL_MAX_THRESHOLD){
			if (channel[CHANNEL_DIFMOTOR_STEERING] > CHANNEL_DIFMOTOR_STEERING_MAX){
				steering = 1.0;
			} else {
				steering = ((float)channel[CHANNEL_DIFMOTOR_STEERING]-CHANNEL_MEDIAN) / ((float)CHANNEL_DIFMOTOR_STEERING_POSITIVE_RANGE);
			}
		} else if(channel[CHANNEL_DIFMOTOR_STEERING] < CHANNEL_MIN_THRESHOLD){
			if (channel[CHANNEL_DIFMOTOR_STEERING] < CHANNEL_DIFMOTOR_STEERING_MIN){
				steering = -1.0;
			} else {
				steering = ((float)channel[CHANNEL_DIFMOTOR_STEERING]-CHANNEL_MEDIAN) / ((float)CHANNEL_DIFMOTOR_STEERING_NEGATIVE_RANGE);
			}
		}
		if(steering != 0.0 || takeover){
			if(!propulsionMessage){
				propulsionMessage = new geometry_msgs::Twist();
			}
			propulsionMessage->angular.z = steering;
		}



		float conveyor = 0.0;
		if(channel[CHANNEL_CONVEYOR_ACTIVATION] > CHANNEL_MAX_THRESHOLD){
			if (channel[CHANNEL_CONVEYOR_ACTIVATION] > CHANNEL_CONVEYOR_ACTIVATION_MAX){
				conveyor = 1.0;
			} else {
				conveyor = ((float)channel[CHANNEL_CONVEYOR_ACTIVATION]-CHANNEL_MEDIAN) / ((float)CHANNEL_CONVEYOR_ACTIVATION_POSITIVE_RANGE);
			}
		} else if(channel[CHANNEL_CONVEYOR_ACTIVATION] < CHANNEL_MIN_THRESHOLD){
			if (channel[CHANNEL_CONVEYOR_ACTIVATION] < CHANNEL_CONVEYOR_ACTIVATION_MIN){
				conveyor = -1.0;
			} else {
				conveyor = ((float)channel[CHANNEL_CONVEYOR_ACTIVATION]-CHANNEL_MEDIAN) / ((float)CHANNEL_CONVEYOR_ACTIVATION_NEGATIVE_RANGE);
			}
		}

		if(conveyor != 0.0 || takeover){
			if(!conveyorMessage){
				conveyorMessage = new geometry_msgs::Twist();
			}
			conveyorMessage->linear.x = conveyor;
		}

	} else {
		//disregarded, no override and no active channels
	}
	check_publishing();
}
