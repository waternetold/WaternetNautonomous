#ifndef BLUETOOTHMANAGER_H_
#define BLUETOOTHMANAGER_H_

#include "ros/ros.h"

#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <ctime>

#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"

#include "DeviceINQ.h"
#include "Enums.h"
#include "BluetoothException.h"
#include "BTSerialPortBinding.h"
#include "OperatorListener.hpp"
#include "NavigationListener.hpp"
#include "BluetoothCommunicator.hpp"

ros::Subscriber bluetooth_operator_propulsion;
ros::Subscriber bluetooth_operator_conveyor;
ros::Subscriber bluetooth_operator_lighting;

ros::Subscriber bluetooth_navigation_pose;

ros::Publisher bluetooth_output;

BTSerialPortBinding* bt;

#endif /* BLUETOOTHMANAGER_H_ */

