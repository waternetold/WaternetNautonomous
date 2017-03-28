##Nautonomous main page

The Nautonomous code is split into multiple packages. Each package is used for a specific purpose. The packages use '.launch' files to create nodes and topics. Below is a brief explanation about each package and the launch files used in that package.

##Configuration
[nautonomous configuration](@ref nautonomous_configuration)
<br />
The nautonomous configuration package is the main package and uses the 'nautonomous_configuration.launch' to run. The launch file include all other packages and their launch files. This file is also used to set parameters e.g. 'simulating' or 'routing'.


##Actuation
The actuation packages receive and output commands. These commands are used for propulsion, conveyor and lighting. 

[nautonomous actuation selector](@ref nautonomous_actuation_selector)
<br />
Select manual or autonomous commands, uses 'output_multiplexer.launch'

[nautonomous actuation simulator](@ref nautonomous_actuation_simulator)
<br />
Output for simulaton, uses 'propulsion_sim.launch' 

[nautonomous actuation synchronizer](@ref nautonomous_actuation_synchronizer)
<br />
Writes commands to the serial output. 

##GPS
[nautonomous gps ublox](@ref nautonomous_gps_ublox)
<br />
nautonomous gps ublox

##Navigation
[nautonomous navigation odometry](@ref nautonomous_navigation_odometry)
<br />
Transforms GPS into UTM.

[nautonomous navigation transform](@ref nautonomous_navigation_transform)
<br />
Combines odom+imu for /tf.

[nautonomous operation action](@ref nautonomous_operation_action)
<br />
Contains MissionServer and MoveBaseActionClient.

##Serverconnection
[nautonomous serverconnection bridge server](@ref nautonomous_serverconnection_bridge_server)
<br />
nautonomous serverconnection bridge server

[nautonomous serverconnection logger server](@ref nautonomous_serverconnection_logger_server)
<br />
nautonomous serverconnection logger server

![Caption text 2](../images/nautonomous_configuration.png)


