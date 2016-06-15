#include "../include/nautonomous_operation_action_client/OperationManager.h"

using namespace std;

int main(int argc, char** argv){
	ros::init(argc, argv, "move_base_action_client");
	ros::NodeHandle nh;

	MissionServer server(nh,"mission_action");
	MoveBaseActionClient moveBase = MoveBaseActionClient();

	ros::Rate r(1);
	r.sleep();
	ros::spinOnce();
	while(ros::ok()){
		ROS_INFO("test...");

		server.getNextGoal();
		moveBase.requestGoal(server.nextPosition_, server.nextOrientation_);

		r.sleep();
		ros::spinOnce();
		//executeOperations();
	}
}
