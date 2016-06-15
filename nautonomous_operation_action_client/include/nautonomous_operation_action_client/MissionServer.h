///*
// * MissionServer.h
// *
// *  Created on: Apr 3, 2016
// *      Author: zeeuwe01
// */
//
#ifndef MISSIONSERVER_H_
#define MISSIONSERVER_H_

#include "ros/ros.h"

#include <actionlib/server/simple_action_server.h>
#include <nautonomous_operation_action_client/MissionAction.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include <tf/transform_listener.h>

typedef actionlib::SimpleActionServer<nautonomous_operation_action_client::MissionAction> Server;

class MissionServer
{

public:

  MissionServer(ros::NodeHandle nh_, std::string name);

  ~MissionServer(void);

  void executeCB(const nautonomous_operation_action_client::MissionGoalConstPtr &goal);

  actionlib::SimpleActionServer<nautonomous_operation_action_client::MissionAction> as_;
    std::string action_name_;
    // create messages that are used to published feedback/result
    nautonomous_operation_action_client::MissionFeedback feedback_;
    nautonomous_operation_action_client::MissionResult result_;
    nautonomous_operation_action_client::MissionGoal goal_;
    geometry_msgs::Point nextPosition_;
    geometry_msgs::Quaternion nextOrientation_;
    void getNextGoal();
};
#endif /* MISSIONSERVER_H_ */
