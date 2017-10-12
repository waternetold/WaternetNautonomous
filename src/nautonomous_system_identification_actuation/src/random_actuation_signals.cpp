#include <ros/ros.h>
#include <ros/console.h>
//PCL specific includes
#include <math.h>
#include <iostream>
#include <geometry_msgs/Twist.h>

// Namespaces
using namespace std;

ros::Publisher vel_pub;

geometry_msgs::Twist msg;

// Publishers
ros::Publisher marker_pub;
ros::Publisher message_pub;

// Initialization
int timescale = 1;
int accscale = 1;

int main (int argc, char** argv)
{
	ros::init (argc, argv,"Random_signal_actuation");
	ros::NodeHandle nh("");
	ros::NodeHandle nh_private("~");
	ros::Rate cycle(1);

	double Begin = ros::Time::now().toSec();
	double Now = ros::Time::now().toSec();
	double Elapsed_time = Now-Begin;

	while (ros::ok())
	{
		// Parameters
		Now = ros::Time::now().toSec();
		Elapsed_time = Now-Begin;

		vel_pub = nh_private.advertise<geometry_msgs::Twist>("cmd_vel",10);
	
		Now = ros::Time::now().toSec();
		Elapsed_time = Now-Begin;

		cout << "Elapsed time is: " << Elapsed_time << endl;
		
		if (Elapsed_time < (timescale * 10))
		{
			msg.linear.x = 0;
			msg.linear.y = 0;
			msg.linear.z = 0;
			msg.angular.x = 0;
			msg.angular.y = 0;
			msg.angular.z = 0;
		}
		else if (Elapsed_time < (timescale * 20))
		{
			msg.linear.x = 0.1 * accscale;
			msg.linear.y = 0;
			msg.linear.z = 0;
			msg.angular.x = 0;
			msg.angular.y = 0;
			msg.angular.z = 0;
		}
		else if (Elapsed_time < (timescale * 30))
		{
			msg.linear.x = 0;
			msg.linear.y = 0.1 * accscale;
			msg.linear.z = 0;
			msg.angular.x = 0;
			msg.angular.y = 0;
			msg.angular.z = 0;
		}
		else if (Elapsed_time < (timescale * 40))
		{
			msg.linear.x = 0;
			msg.linear.y = 0;
			msg.linear.z = 0.1 * accscale;
			msg.angular.x = 0;
			msg.angular.y = 0;
			msg.angular.z = 0;
		}
		else if (Elapsed_time < (timescale * 50))
		{
			msg.linear.x = 0;
			msg.linear.y = 0;
			msg.linear.z = 0;
			msg.angular.x = 0.1 * accscale;
			msg.angular.y = 0;
			msg.angular.z = 0;
		}
		else if (Elapsed_time < (timescale * 60))
		{
			msg.linear.x = 0;
			msg.linear.y = 0;
			msg.linear.z = 0;
			msg.angular.x = 0;
			msg.angular.y = 0.1 * accscale;
			msg.angular.z = 0;
		}
		else if (Elapsed_time < (timescale * 70))
		{
			msg.linear.x = 0;
			msg.linear.y = 0;
			msg.linear.z = 0;
			msg.angular.x = 0;
			msg.angular.y = 0;
			msg.angular.z = 0.1 * accscale;
		}
		else
		{
			msg.linear.x = 0;
			msg.linear.y = 0;
			msg.linear.z = 0;
			msg.angular.x = 0;
			msg.angular.y = 0;
			msg.angular.z = 0;
		}

		vel_pub.publish(msg);
		
		cycle.sleep();
	}
}
