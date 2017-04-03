from PIL import Image
import pyproj
import yaml

from nav_msgs.msg import *
from std_msgs.msg import *

def fromWgsToRd(coords):
        
        Rp = [0,1,2,0,1,3,1,0,2]
        Rq = [1,1,1,3,0,1,3,2,3]
        Rpq = [190094.945,-11832.228,-114.221,-32.391,-0.705,-2.340,-0.608,-0.008,0.148]

        Sp = [1,0,2,1,3,0,2,1,0,1]
        Sq = [0,2,0,2,0,1,2,1,4,4]
        Spq = [309056.544,3638.893,73.077,-157.984,59.788,0.433,-6.439,-0.032,0.092,-0.054]
	
	cal = []
	for coord in coords:
		dPhi = 0.36 * ( coord[0] - 52.15517440 )
		dLam = 0.36 * ( coord[1] - 5.38720621 )

		X = 0
		Y = 0

		for r in range( len( Rpq ) ):
		    X = X + ( Rpq[r] * dPhi**Rp[r] * dLam**Rq[r] ) 
		X = 155000 + X

		for s in range( len( Spq ) ):
		    Y = Y + ( Spq[s] * dPhi**Sp[s] * dLam**Sq[s] )
		Y = 463000 + Y
		cal.append([X, Y])

        return cal

def arange(cropped):
	dist = []
	for x in range(2):
		current = cropped[0][x]
		if x == 0:
			if cropped[0][x] < cropped[1][x]:
				dist.append(cropped[1][x] - cropped[0][x])
				cropped[0][x] = cropped[1][x]
				cropped[1][x] = current
			else:
				dist.append(cropped[0][x] - cropped[1][x])
		else:
			if cropped[0][x] > cropped[1][x]:
				dist.append(cropped[0][x] - cropped[1][x])
				cropped[0][x] = cropped[1][x]
				cropped[1][x] = current
			else:
				dist.append(cropped[1][x] - cropped[0][x])
	return dist, cropped

def toFloatCordinate(line):
	output = [];
	for row in line:
		current = row.split(',')
		output.append([float(current[0]), float(current[1])])
	return output

def crop(cropped):
	with open("/home/ubuntu/ROS/nautonomous_ws4/src/WaternetNautonomous/WaternetNautonomousNavigation/nautonomous_navigation_planner/scripts/total.yaml") as f:
		map_data = yaml.safe_load(f)

	resolution = map_data["resolution"]
	origin = map_data["origin"]

	test_image = "/home/ubuntu/ROS/nautonomous_ws4/src/WaternetNautonomous/WaternetNautonomousNavigation/nautonomous_navigation_planner/scripts/utm_amsterdam.png"
	original = Image.open(test_image)

	cropped[0][0] += 100
	cropped[1][0] -= 100
	cropped[1][1] += 100
	cropped[0][1] -= 100
	
	top = (5806351 - cropped[1][1]) * 2
	bottom = (5806351 - cropped[0][1]) * 2
	left = (625550 - cropped[1][0]) * -2
	right = (625550 - cropped[0][0]) * -2	

	#print "INFO: ", int(left), int(top), int(right), int(bottom)
	
	cropped_example = original.crop((int(left), int(top), int(right), int(bottom)))
	cropped_example.save("/home/ubuntu/ROS/nautonomous_ws4/src/WaternetNautonomous/WaternetNautonomousNavigation/nautonomous_navigation_planner/scripts/amsterdam.png")

	map_data["image"] = "amsterdam.png"

	height = -3000 + (6000 - int(bottom) / 2) 
	width = -3000 + int(left) / 2

	map_data["origin"] = [width, height, 0.0]
	with open("/home/ubuntu/ROS/nautonomous_ws4/src/WaternetNautonomous/WaternetNautonomousNavigation/nautonomous_navigation_planner/scripts/amsterdam.yaml", "w") as f:
		yaml.dump(map_data, f)

def run(full):
	real = toFloatCordinate([full[0], full[2]])	
	p = pyproj.Proj(proj='utm', zone=31, ellps='WGS84')
	
	cropped = []
	locate = [[0,0],[0,0]]
	for coord in real:
		x,y = p(coord[1], coord[0])
		cropped.append([x, y])

	locate[0][1] = -3000 + (6000 - (5803351 - cropped[0][1]))
	locate[0][0] = -3000 + ((628550 - cropped[0][0]) * -1)
	

	position, cropped = arange(cropped)
	crop(cropped)
	return locate
