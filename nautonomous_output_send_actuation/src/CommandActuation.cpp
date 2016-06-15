#include "../include/nautonomous_output_send_actuation/CommandActuation.hpp"

int main(int argc, char **argv)
{

  ros::init(argc, argv, "command_actuation");

  ros::NodeHandle n;

  ros::Subscriber propulsionSub = n.subscribe("multiplexed_propulsion", 1000, propulsionCallback);
  ros::Subscriber conveyorSub = n.subscribe("multiplexed_conveyor", 1000, conveyorCallback);
  ros::Subscriber lightingSub = n.subscribe("multiplexed_lighting", 1000, lightingCallback);
  ROS_INFO("Subscribed");

  actuation_init_serial();
  ROS_INFO("Serial initted");

  ros::Rate r(25);

  while(ros::ok()){
	  if(propulsion_message){
		  actuation_send_twist(propulsion_message, true);
		  delete propulsion_message;
		  propulsion_message = nullptr;
	  }
	  if(conveyor_message){
		  actuation_send_twist(conveyor_message, false);
		  delete conveyor_message;
		  conveyor_message = nullptr;
	  }

	  //ROS_INFO("Send propulsion %d",send_test());
	  /*if(lighting_message)
	  {
		  ROS_INFO("Send actuation %d", actuation_send_bool(lighting_message));
	  }*/
	  r.sleep();
	  ros::spinOnce();
  }

  actuation_deinit_serial();

  return 0;
}
