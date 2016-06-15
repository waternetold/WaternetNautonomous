#include "../include/nautonomous_cooperation_bluetooth_node/BluetoothCommunicator.hpp"

void sendBluetoothCommand(char* buffer, uint8_t size, ros::Publisher publisher) {
	try {
		ROS_INFO("buffer %s", buffer);

		bt->Write(buffer, size);

		if(publisher){
			std_msgs::String msg;
			msg.data = string(buffer);
			publisher.publish(msg);
		}

	} catch (const BluetoothException& e) {
		cout << "Error: " << e.what() << endl;
		bluetooth_ok = false;
	}
}

void sendBluetoothCommands() {
	bool send = false;
	int size = 50;
	if (propulsionTwist) {

		char propulsionBuffer[size];
		sprintf(propulsionBuffer, "p:%.3f;%.3f;%.3f;%.3f;%.3f;%.3f",
				propulsionTwist->linear.x, propulsionTwist->linear.y,
				propulsionTwist->linear.z, propulsionTwist->angular.x,
				propulsionTwist->angular.y, propulsionTwist->angular.z);
		sendBluetoothCommand(propulsionBuffer, size, bluetooth_output);

		delete propulsionTwist;
		propulsionTwist = nullptr;

		send = true;
	}
	if (conveyorTwist) {

		char conveyorBuffer[size];
		sprintf(conveyorBuffer, "c:%.3f;%.3f;%.3f;%.3f;%.3f;%.3f",
				conveyorTwist->linear.x, conveyorTwist->linear.y,
				conveyorTwist->linear.z, conveyorTwist->angular.x,
				conveyorTwist->angular.y, conveyorTwist->angular.z);
		sendBluetoothCommand(conveyorBuffer, size, bluetooth_output);

		delete conveyorTwist;
		conveyorTwist = nullptr;

		send = true;
	}
	if (lightingBool) {

		char lightingBuffer[size];
		sprintf(lightingBuffer, "l:%i", lightingBool->data);
		sendBluetoothCommand(lightingBuffer, size, bluetooth_output);

		delete lightingBool;
		lightingBool = nullptr;

		send = true;
	}
	char* poseBuffer = nullptr;
	if (goalPoseStamped) {

		char poseBuffer[size];
		sprintf(poseBuffer, "g:%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3fs",
				goalPoseStamped->pose.position.x, goalPoseStamped->pose.position.y,
				goalPoseStamped->pose.position.z, goalPoseStamped->pose.orientation.x,
				goalPoseStamped->pose.orientation.y, goalPoseStamped->pose.orientation.z,
				goalPoseStamped->pose.orientation.w);
		sendBluetoothCommand(poseBuffer, size, bluetooth_output);

		delete goalPoseStamped;
		goalPoseStamped = nullptr;

		send = true;
	}

	if(!send){

		char messageBuffer[size];
		sprintf(messageBuffer, "n:0");
		sendBluetoothCommand(messageBuffer, size, bluetooth_output);

		send = true;
	}

}
