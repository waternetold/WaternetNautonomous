#ifndef BLUETOOTHCOMMUNICATOR_H
#define BLUETOOTHCOMMUNICATOR_H

#include "ros/ros.h"
#include <string>

#include "OperatorListener.hpp"
#include "NavigationListener.hpp"
#include "BluetoothManager.hpp"

using namespace std;

bool bluetooth_ok = true;

void sendBluetoothCommand(char* buffer, uint8_t size, ros::Publisher publisher);

void sendBluetoothCommands();

#endif /* BLUETOOTHCOMMUNICATOR_H */
