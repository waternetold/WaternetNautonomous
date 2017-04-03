#!/usr/bin/env python

import rospy
import pyproj
import json
import os
import math

import networkx as nx
import matplotlib.pyplot as plt

from vertex import Vertex
from geometry_msgs.msg import Point, Quaternion
from nautonomous_navigation_planner.srv import *
from astarSearch import *
from crop import *
from orientation import orientation
from sensor_msgs.msg import NavSatFix

longitude = 0;
latitude = 0;

def callback(data):
	global longitude, latitude
	longitude = data.longitude
	latitude = data.latitude

def findClosestWaypoints(waypoint):
	closestNode = 0
	closestDistance = 1000000
    
	for node in G.nodes():
		distance = euclideanDistance(waypoint, node)
		if distance == 0.0:
			return waypoint
		elif(distance < closestDistance):
			closestDistance = distance
			closestNode = node

	if(closestNode == 0):
		return False

	closestNodes = [closestNode]

	nextNode = 0    
	nextDistance = 1000000

	for edge in G.edges():

		if(closestNode in edge):
			edgeNode = 0
			if(closestNode == edge[0]):
				edgeNode = edge[1]
			elif(closestNode == edge[1]):
				edgeNode = edge[0]              

			distance = euclideanDistance(edgeNode, waypoint)
			if(distance < nextDistance):
				nextDistance = distance
				nextNode = edgeNode

	if(nextNode == 0):
		return False

	closestNodes.append(nextNode)

	return closestNodes

def handle_navigation(req):
	coordinates = [latitude, longitude, req.c, req.d]
	start = str(coordinates[0]) + "," + str(coordinates[1])
	goal = str(coordinates[2]) + "," + str(coordinates[3])

	closestStart = findClosestWaypoints(start)
	closestGoal = findClosestWaypoints(goal)

	searchResult = []

	shortestDistance = 10000000
	shortestResult = []
	for i in range(0, 4):
		result,distance = aStarSearch(G, closestStart[(i/2)], closestGoal[not (i%2)])
		if distance < shortestDistance:
			shortestDistance = distance
			shortestResult = result
			shortestResult.insert(0, closestStart[(i/2)])
			shortestResult.insert(0, start)
			shortestResult.append(closestGoal[not (i%2)])
			shortestResult.append(goal)

	pin = run(shortestResult)

	route = []
	for j in range(0, 4):
		short = shortestResult[j]
		dots = short.split(',')
		route.append([float(dots[0]), float(dots[1])])

	p = pyproj.Proj(proj='utm', zone=31, ellps='WGS84')

	rd_route = []
	for coord in route:
		x,y = p(coord[1], coord[0])
		rd_route.append([x, y])

	os.system("rosrun map_server map_server amsterdam.yaml&")
	os.system("")

	z, w = orientation(rd_route)
	#print "x:", rd_route[1][0] - 121000, "y:", rd_route[1][1] - 486500, "z:", z, "w:", w

	#return pin[0][0], pin[0][1], z, w

	#node_colors = ["green" if n in shortestResult else "white" for n in G.nodes()]

	#pos=nx.get_node_attributes(G,'pos')
	#nx.draw_networkx_nodes(G, pos=pos, node_color=node_colors)
	#nx.draw_networkx_edges(G, pos=pos)
	#plt.show()
	print "Dit is een test..."
	print rd_route[1][0]
	return rd_route[1][0] - 628550, rd_route[1][1] - 5803351, z, w

def navigatoin_server():
	rospy.init_node('navigation_server')
	sub = rospy.Subscriber("gps/fix", NavSatFix, callback)
	rate = rospy.Rate(10)
	while longitude == 0:
		rospy.loginfo("waiting fix")
		rate.sleep()
	s = rospy.Service('add_two_ints', AddTwoInts, handle_navigation)
	rospy.loginfo("Waiting for coordinates...")	
	print "Waiting for coordinates..."
	rospy.spin()

if __name__ == "__main__":
	print "construct graaf"
	G = nx.Graph()
	v = []

	__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))

	with open(os.path.join(__location__, 'intersections.json')) as data_file:    
		data = json.load(data_file)
		for node in data:
			#if(not(node["id"] in G.nodes())):
			v.append(Vertex(node["id"], node["adjacent"], node["connected"]))
			position = node["id"].split(",")
			positionPoints = [float(position[1]),float(position[0])]                      
			G.add_node(node["id"],pos=positionPoints)

		for node in data:
			connectedNodes = node["connected"] 
			for connected in connectedNodes:
				#if(not((connected,node["id"]) in G.edges())):
				G.add_edge(node["id"],connected, weight=(euclideanDistance(node["id"],connected)*1000))
	
	navigatoin_server()
