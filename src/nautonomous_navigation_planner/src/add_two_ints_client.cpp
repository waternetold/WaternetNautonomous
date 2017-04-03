#include "ros/ros.h"
#include "nautonomous_navigation_planner/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "add_two_ints_client");
	
	float current[] = {52.36727, 4.93093};
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<nautonomous_navigation_planner::AddTwoInts>("add_two_ints");
	nautonomous_navigation_planner::AddTwoInts srv;
	srv.request.a = 0;
	srv.request.b = 0;
	srv.request.c = 52.36905;
	srv.request.d = 4.89248;
	while (ros::ok())
	{
		srv.request.a = current[0];
		srv.request.b = current[1];
		if (client.call(srv))
		{
			int x = srv.response.x;
			int y = srv.response.y;
			float lat = srv.response.lat;
			float lon = srv.response.lon;
			
			ROS_INFO("x: %d, y: %d / lat: %f, lon: %f", x, y, lat, lon);
		}
		else
		{
			ROS_ERROR("Failed to call service add_two_ints");
			return 1;
		}
	}

	return 0;
}
