/*
 * SendActuation.hpp
 *
 *  Created on: Apr 16, 2016
 *      Author: zeeuwe01
 */

#ifndef SENDACTUATION_HPP_
#define SENDACTUATION_HPP_

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "Serial.hpp"
#include <iostream>
#include <vector>

#define SABERTOOTH
//#define SABERTOOTH_TEST
#include "Sabertooth.hpp"
#ifdef SABERTOOTH
#include "Sabertooth.hpp"
#endif


using namespace std;

serial::Serial* actuation_serial;

bool actuation_init_serial();

void actuation_deinit_serial();

int send_test();

size_t actuation_send(std::string message_string);

size_t actuation_send_twist(geometry_msgs::Twist* twist, bool propulsion);


#endif /* SENDACTUATION_HPP_ */
