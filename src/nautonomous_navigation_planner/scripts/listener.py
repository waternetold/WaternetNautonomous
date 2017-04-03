#!/usr/bin/env python
import rospy
from std_msgs.msg import String,Int32,Float32MultiArray,MultiArrayLayout,MultiArrayDimension
import pyproj

import json
import networkx as nx

import matplotlib.pyplot as plt
from vertex import Vertex
from astarSearch import *
from crop import *


def talker(route):
	pub = rospy.Publisher('route', Float32MultiArray, queue_size = 10)
	rate = rospy.Rate(10) # 10hz
	mat = Float32MultiArray()
	mat.layout.dim.append(MultiArrayDimension())
	mat.layout.dim[0].label = "route"
	mat.layout.dim[0].size = 2
	mat.layout.dim[0].stride = 3*3
	mat.layout.data_offset = 0
	mat.data = route

	pub.publish(mat)


G = nx.Graph()
v = []
with open('/home/wiebe/ros_workspace/src/waternet_tutorial_pubsub/script/intersections.json') as data_file:    
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

def callback(data):
	coordinates = data.data
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

	run(shortestResult)
	route = shortestResult[2]

	route = route.split(',')
	p = pyproj.Proj(proj='utm', zone=31, ellps='WGS84')
	lon = float(route[0])
	lat = float(route[1])

	x,y = p(lat, lon)
	x = round(x,0)
	y = round(y,0)

	center = [628662, 5803411]
	x -= center[0]
	y -= center[1] 
	
	point = [x, y, lon, lat]

	if __name__ == '__main__':
		try:
			#talker(point)
			print(point)
		except rospy.ROSInterruptException:
			pass

	#for point in shortestResult:
	#	print "new google.maps.LatLng(" + point + "),";
	#print "-----------"

	#node_colors = ["green" if n in shortestResult else "white" for n in G.nodes()]

	#pos=nx.get_node_attributes(G,'pos')
	#nx.draw_networkx_nodes(G, pos=pos, node_color=node_colors)
	#nx.draw_networkx_edges(G, pos=pos)
	#plt.show()

def listener():
	rospy.init_node('listener', anonymous=True)

	rospy.Subscriber('coordinates', Float32MultiArray, callback)

	rospy.spin()

if __name__ == '__main__':
	listener()