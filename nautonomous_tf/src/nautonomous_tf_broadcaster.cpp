#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include "geometry_msgs/Pose.h"

void poseCallback(const geometry_msgs::Pose::ConstPtr& msg){
    static tf::TransformBroadcaster br;
    ROS_INFO("received pose");
    tf::Transform transform;
    transform.setOrigin( tf::Vector3(msg->position.x, msg->position.y, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, msg->orientation.w);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "nautonomous_odom"));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "nautonomous_tf_publisher");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/nautonomous/pose", 100, &poseCallback);
  tf::TransformBroadcaster broadcaster;

  ros::Rate rate(100);

  while(ros::ok()){
    /*broadcaster.sendTransform(
          tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
          tf::Vector3(0.0, 0.0, 0.0)), ros::Time::now(),
           "nautonomous_odom", "base_footprint"));*/
    /*broadcaster.sendTransform(
            tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
            tf::Vector3(0.0, 0.0, 0.0)), ros::Time::now(),
             "odom", "base_link"));*/
    broadcaster.sendTransform(
          tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
          tf::Vector3(1.0, 0.0, 0.5)), ros::Time::now(),
           "base_link", "camera_link"));

broadcaster.sendTransform(
          tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
          tf::Vector3(0.2, -0.2, 1.0)), ros::Time::now(),
           "base_link", "gps_link"));

broadcaster.sendTransform(
          tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
          tf::Vector3(-0.2, 0.5, 0.5)), ros::Time::now(),
           "base_link", "imu_link"));
    broadcaster.sendTransform(
          tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
          tf::Vector3(0.0, 0.0, 0.0)), ros::Time::now(),
           "base_link", "base_footprint"));
    broadcaster.sendTransform(
          tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
          tf::Vector3(0.0, 0.0, 0.0)), ros::Time::now(),
           "map", "odom_combined"));
    /*broadcaster.sendTransform(
		tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
        tf::Vector3(0.0, -0.5, 0.2)), ros::Time::now(),
         "base_footprint", "pixhawk_frame"));
    broadcaster.sendTransform(
        tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
        tf::Vector3(-0.2, 0.2, 0.4)), ros::Time::now(),
         "base_footprint", "gps_frame"));
    broadcaster.sendTransform(
        tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
        tf::Vector3(0.0, -0.5, 0.3)), ros::Time::now(),
         "base_footprint", "gps2_frame"));
    broadcaster.sendTransform(
        tf::StampedTransform( tf::Transform(tf::Quaternion(0, 0, 0 , 1),
        tf::Vector3(0.0, 0.5, 0.3)), ros::Time::now(),
         "base_footprint", "camera_frame"));*/
	rate.sleep();
    ros::spinOnce();
  }

  ros::spin();
  return 0;
}
