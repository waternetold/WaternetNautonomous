#include "../include/nautonomous_operation_action_client/MissionServer.h"

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <nautonomous_operation_action_client/MissionAction.h>


int missionIndex = 0;
const int maxMission = 6;

/*
 *WPK
double missionCoordinates[maxMission][2][4] = {
//	Position(44,640, -20,119, 0,000), Orientation(0,000, 0,000, 0,879, -0,477) = Angle: -2,148
		{ { 44.6, -20.1, 0.0, 0.0 }, { 0.0, 0.0, 0.879, -0.477 } },
		//	Position(27,983, -27,779, 0,000), Orientation(0,000, 0,000, 0,827, 0,562) = Angle: 1,948
		{ { 28.0, -27.8, 0.0, 0.0 }, { 0.0, 0.0, 0.827, 0.562 } },
		//	Position(16,250, -4,192, 0,000), Orientation(0,000, 0,000, 0,177, 0,984) = Angle: 0,356
		{ { 16.3, -4.2, 0.0, 0.0 }, { 0.0, 0.0, 0.177, 0.984 } },
		//	Position(34,772, 29,221, 0,000), Orientation(0,000, 0,000, -0,574, 0,819) = Angle: -1,224
		{ { 34.8, 29.2, 0.0, 0.0 }, { 0.0, 0.0, -0.574, 0.819 } } };
*/
double missionCoordinates[maxMission][2][4] = {

        { { -27.8, 31.8, 0.0, 0.0 }, { 0.0, 0.0, 0.863, 0.505 } },

        { { -53.8, 67.8, 0.0, 0.0 }, { 0.0, 0.0, 0.948, 0.319 } },

        { { -75.8, 104.8, 0.0, 0.0 }, { 0.0, 0.0, 0.429, 0.903 } },

        { { -26.8, 97.8, 0.0, 0.0 }, { 0.0, 0.0, -0.255, 0.967 } },

        { { 39.2, 52.8, 0.0, 0.0 }, { 0.0, 0.0, 0.905, -0.425} },

        { { 8.2, -3.2, 0.0, 0.0 }, { 0.0, 0.0, 0.905, -0.425 } } };
/*
double missionCoordinates[maxMission][2][4] = {

        { { -27.9, 32.6, 0.0, 0.0 }, { 0.0, 0.0, 0.87, 0.49 } },

        { { -51.6, 64.2, 0.0, 0.0 }, { 0.0, 0.0, -0.42, 0.91 } } };*/

MissionServer::MissionServer(ros::NodeHandle nh_, std::string name) :
		as_(nh_, name.c_str(), boost::bind(&MissionServer::executeCB, this, _1),
				false), action_name_(name) {
//	ROS_INFO("Started action %s", action_name.c_str());
	as_.start();
}

MissionServer::~MissionServer(void) {
}

void MissionServer::executeCB(
		const nautonomous_operation_action_client::MissionGoalConstPtr &goal) {
	// helper variables

	goal_.operation = goal->operation;
	nextPosition_ = geometry_msgs::Point(goal_.operation.path[0]);
	nextOrientation_ = geometry_msgs::Quaternion(
			goal_.operation.orientations[0]);

	ros::Rate r(1);
	bool success = true;

	// push_back the seeds for the fibonacci sequence
	feedback_.feedback.progression = 50;
	feedback_.feedback.status = "Ok";

	// publish info to the console for the user
	ROS_INFO("received goal");

	as_.publishFeedback(feedback_);

	r.sleep();

	if (success) {
		result_.result.progression = 100;
		result_.result.status = feedback_.feedback.status;

		// set the action state to succeeded
		as_.setSucceeded(result_);
	}
}

void MissionServer::getNextGoal(/*tf::TransformListener* listener*/) {
	/*tf::StampedTransform transform;
	try {
		ros::Time now = ros::Time::now();
		listener->waitForTransform("/odom", "/base_link", now,
				ros::Duration(1.0));
		 listener->lookupTransform("/odom", "/base_link",
		                        now, transform);
	} catch (tf::TransformException ex) {
		ROS_ERROR("%s", ex.what());
		ros::Duration(1.0).sleep();
	}
	ROS_INFO("Transform from map to odom (%f,%f)", transform.getOrigin().y(), transform.getOrigin().x());
*/
	nextPosition_ = geometry_msgs::Point();
	nextPosition_.x = missionCoordinates[missionIndex][0][0];
	nextPosition_.y = missionCoordinates[missionIndex][0][1];
	nextPosition_.z = missionCoordinates[missionIndex][0][2];
	ROS_INFO("Next point is %d (%f, %f, %f)", missionIndex, nextPosition_.x, nextPosition_.y,
			nextPosition_.z);

	nextOrientation_ = geometry_msgs::Quaternion();
	nextOrientation_.x = missionCoordinates[missionIndex][1][0];
	nextOrientation_.y = missionCoordinates[missionIndex][1][1];
	nextOrientation_.z = missionCoordinates[missionIndex][1][2];
	nextOrientation_.w = missionCoordinates[missionIndex][1][3];
	ROS_INFO("Next orientation is (%f, %f, %f, %f)", nextOrientation_.x,
			nextOrientation_.y, nextOrientation_.z, nextOrientation_.w);



	missionIndex = (missionIndex + 1) % maxMission;

}

