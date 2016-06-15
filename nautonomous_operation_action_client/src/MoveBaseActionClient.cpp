/*#include "nautonomous_operation_action_client/MoveBaseAction.h"

 MoveBaseAction::MoveBaseAction(){

 }

 int MoveBaseAction::requestGoal(geometry_msgs::Point point, geometry_msgs::Quaternion quaternion){
 //ros::init(argc, argv, "simple_navigation_goals");

 //tell the action client that we want to spin a thread by default
 /*  MoveBaseClient ac("move_base", true);

 //wait for the action server to come up
 int i = 0;
 while(!ac.waitForServer(ros::Duration(1.0))){
 ROS_INFO("Waiting for the move_base action server to come up");
 i++;
 break;
 }
 if(i > 0){
 return 0;
 }

 move_base_msgs::MoveBaseGoal goal;

 //we'll send a goal to the robot to move 1 meter forward
 goal.target_pose.header.frame_id = "base_link";
 goal.target_pose.header.stamp = ros::Time::now();

 goal.target_pose.pose.position = point;
 goal.target_pose.pose.orientation = quaternion;

 ROS_INFO("Sending goal");
 ac.sendGoal(goal);

 ac.waitForResult();

 if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
 ROS_INFO("Hooray, the base moved 1 meter forward");
 else
 ROS_INFO("The base failed to move forward 1 meter for some reason");
 *//*
 return 0;
 }*/

#include <../include/nautonomous_operation_action_client/MoveBaseActionClient.h>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <../include/actionlib/client/simple_action_client.h>

MoveBaseActionClient::MoveBaseActionClient() {
	ac = new MoveBaseClient("move_base", true);
}

MoveBaseActionClient::~MoveBaseActionClient() {
	if(ac){
		delete ac;
	}
}

int MoveBaseActionClient::requestGoal(geometry_msgs::Point point, geometry_msgs::Quaternion quaternion) {
	while (!ac->waitForServer(ros::Duration(5.0))) {
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;

	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "odom_combined";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = point.x;
	goal.target_pose.pose.position.y = point.y;
	goal.target_pose.pose.position.z = point.z;

	goal.target_pose.pose.orientation.x = quaternion.x;
	goal.target_pose.pose.orientation.y = quaternion.y;
	goal.target_pose.pose.orientation.z = quaternion.z;
	goal.target_pose.pose.orientation.w = quaternion.w;

	ROS_INFO("Sending goal ");
	ac->sendGoal(goal);

	ac->waitForResult();

	if (ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Hooray, the base moved 1 meter forward");
	else
		ROS_INFO("The base failed to move forward 1 meter for some reason");

	return 0;
}

