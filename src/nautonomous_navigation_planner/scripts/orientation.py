#!/usr/bin/env python

import math

def tangensInverse(x, y):
	sides = float(y)/float(x)
	if (x > 0):
		return math.degrees(math.atan(sides))
	if(y > 0):
		return 90 - math.degrees(math.atan(sides))
	elif (y < 0):
		return -90 - math.degrees(math.atan(sides))
 
def orientation(route):
 	if(len(route) >= 4):
		a = route[3][0] - route[2][0]
		b = route[3][1] - route[2][1]

		if (a == 0 and b == 0):
			angular = 0
		elif (a == 0):
			if (b > 0):
				angular = 90
			else:
				angular = -90
		elif (b == 0):
			if (a > 0):
					angular = 0
			else:
				angular = 180
		else:
			angular = tangensInverse(a, b)
	else:
		angular = 0

	z = round(math.sin(math.radians(angular/2)), 3)
	w = round(math.cos(math.radians(angular/2)), 3)
	return z, w
