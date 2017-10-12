#include<ros/ros.h>
#include<nav_msgs/OccupancyGrid.h>
#include<tf/transform_broadcaster.h>
#include<vector>



void OriginCallback (const nav_msgs::MapMetaData::ConstPtr& data_msg)
{
	tf::TransformBroadcaster br;
	tf::Transform transform;

	std::cout << "Found origin is: (" << data_msg->origin.position.x << ", " << data_msg->origin.position.y << ", " << data_msg->origin.position.z << ")" << std::endl;

	transform.setOrigin( tf::Vector3(data_msg->origin.position.x,data_msg->origin.position.y,data_msg->origin.position.z) );
	transform.setRotation( tf::Quaternion(0,0,0,0) );

	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "map_tf_broadcaster");
	ros::NodeHandle node;

	ros::Subscriber pos_sub = nh.subscribe<nav_msgs::MapMetaData>("/navigation/map/server/map_metadata",1,OriginCallback);

	ros::Rate loop(10);

	while (node.ok())
	{

		tf::TransformBroadcaster br;
		tf::Transform transform;

		transform.setOrigin( tf::Vector3(0,0,0) );
		transform.setRotation( tf::Quaternion(0,0,1,1).normalize() );

		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));

		loop.sleep();

	}

	
}
