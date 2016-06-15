#include "../include/nautonomous_output_operator_lowlevel/OperatorLowLevel.hpp"
#include "../include/nautonomous_output_operator_lowlevel/OperatorRCBridge.hpp"

int main(int argc, char **argv) {

	ros::init(argc, argv, "operator_lowlevel");

	ros::NodeHandle n;

	ros::Subscriber inputPropulsion = n.subscribe("/operator_propulsion_vel", 1000, propulsionROSCallback);
	ros::Subscriber inputConveyor = n.subscribe("/operator_conveyor_vel", 1000, conveyorROSCallback);
	ros::Subscriber inputLighting = n.subscribe("/operator_lighting_vel", 1000, lightingROSCallback);

	ros::Subscriber inputRC = n.subscribe("/mavros/rc/in", 1000, rcCallback);
	ros::Subscriber inputSub = n.subscribe("/bluetooth_operator", 1000, bluetoothCallback);

	propulsionPub = n.advertise<geometry_msgs::Twist>("manual_propulsion",
			1000);
	conveyorPub = n.advertise<geometry_msgs::Twist>("manual_conveyor", 1000);
	lightingPub = n.advertise<std_msgs::Bool>("manual_lighting", 1000);

	while(ros::ok()){
		ros::spin();
	}

	return 0;
}
