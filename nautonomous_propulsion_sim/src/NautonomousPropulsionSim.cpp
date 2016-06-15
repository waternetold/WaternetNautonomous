#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>

geometry_msgs::Twist nautonomous_twist;
nav_msgs::OccupancyGrid nautonomous_occupancy_grid;

double vx = 0;
double vy = 0;
double vth = 0;

void propulsionCallback(const geometry_msgs::Twist::ConstPtr& twist) {
	nautonomous_twist.linear.x = twist->linear.x;
	nautonomous_twist.linear.y = twist->linear.y;
	nautonomous_twist.linear.z = twist->linear.z;

	nautonomous_twist.angular.x = twist->angular.x;
	nautonomous_twist.angular.y = twist->angular.y;
	nautonomous_twist.angular.z = twist->angular.z;

	vx = twist->linear.x;
	vy = twist->linear.y;
	vth = twist->angular.z;

}

void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& occupancy) {
	nautonomous_occupancy_grid.data = occupancy->data;
	nautonomous_occupancy_grid.header = occupancy->header;
	nautonomous_occupancy_grid.info = occupancy->info;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "nautonomous_propulsion_sim");

	ros::NodeHandle n;

	ros::Subscriber propulsionSubscriber = n.subscribe(
			"/multiplexed_propulsion", 10, propulsionCallback);

	//ros::Subscriber propulsionSubscriber = n.subscribe(
	//			"/costmap_2d/grid", 1000, mapCallback);

	ros::Subscriber mapSubscriber = n.subscribe("/map", 10, mapCallback);

	ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("/odom_combined", 10); //odom_combined

	tf::TransformBroadcaster odom_broadcaster;

	double x = 0.0;//629267.0;
	double y = 0.0;//5807159.0;
	double th = 0.0;

	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = ros::Time::now();

    	ros::Rate r(15);
	while (n.ok()) {

		ros::spinOnce();               // check for incoming messages
		current_time = ros::Time::now();

		//compute odometry in a typical way given the velocities of the robot
		double dt = (current_time - last_time).toSec();
		double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
		double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
		double delta_th = vth * dt;

		x += delta_x;
		y += delta_y;
		th += delta_th;
		double degrees = (th * 180.0 / M_PI);
		//x and y to index the occupancy grid map.
		if(nautonomous_occupancy_grid.info.height){
		int index_x = nautonomous_occupancy_grid.info.height
				- (abs(x + nautonomous_occupancy_grid.info.origin.position.x)
						/ nautonomous_occupancy_grid.info.resolution);
		int index_y = ((y - nautonomous_occupancy_grid.info.origin.position.y)
				/ nautonomous_occupancy_grid.info.resolution);
		ROS_INFO("(%4.2f, %4.2f | %4.2f [%4.2f]) is index (%d, %d)", x, y, th, degrees, index_x, index_y);
        int index = nautonomous_occupancy_grid.info.height * index_y + index_x;
        if (index >= 0 && index <= (nautonomous_occupancy_grid.info.height*nautonomous_occupancy_grid.info.width)) {
			int value = nautonomous_occupancy_grid.data[index];
			//ROS_INFO("index %d value %d", index, value);

			if (value > 50) {
				//reverse action
				x -= delta_x;
				y -= delta_y;
				th -= delta_th;
			}
        }
}

		//since all odometry is 6DOF we'll need a quaternion created from yaw
		geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(
				th);

		//first, we'll publish the transform over tf
		geometry_msgs::TransformStamped odom_trans;
		odom_trans.header.stamp = current_time;
		odom_trans.header.frame_id = "odom_combined";
		odom_trans.child_frame_id = "base_link";

		odom_trans.transform.translation.x = x;
		odom_trans.transform.translation.y = y;
		odom_trans.transform.translation.z = 0.0;
		odom_trans.transform.rotation = odom_quat;

		//send the transform
		odom_broadcaster.sendTransform(odom_trans);

		//next, we'll publish the odometry message over ROS
		nav_msgs::Odometry odom;
		odom.header.stamp = current_time; 
		odom.header.frame_id = "odom_combined"; //odom_combined

		//set the position
		odom.pose.pose.position.x = x;
		odom.pose.pose.position.y = y;
		odom.pose.pose.position.z = 0.0;
		odom.pose.pose.orientation = odom_quat;

		//set the velocity
		odom.child_frame_id = "base_link"; //base_link
		odom.twist.twist.linear.x = vx;
		odom.twist.twist.linear.y = vy;
		odom.twist.twist.angular.z = vth;

		//publish the message
		odom_pub.publish(odom);

		last_time = current_time;
		r.sleep();
	}

	return 0;
}
