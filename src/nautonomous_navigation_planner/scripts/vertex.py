import json

class Vertex: #intersection
    def __init__(self, node, adjacent = None, connected = None):
        self.id = node#["trafficlink_id"]
        
        if(connected != None):
            self.adjacent = adjacent
        else:
            self.adjacent = []
            
        if(connected != None):
            self.connected = connected
        else:
            self.connected = []

    def __str__(self):
        return str(self.id) + ' adjacent: ' + str([x.id for x in self.adjacent])

    def add_neighbor(self, neighbor, weight=0.0):
        self.adjacent[neighbor] = weight
        
    def add_adjacent(self, identifier, identifier2):
        if(not(identifier in self.adjacent)):
            self.adjacent.append(identifier)
        if(not(identifier2 in self.adjacent)):
            self.adjacent.append(identifier2)

    def add_connected(self, identifier):
        if(not(identifier in self.connected) and not(identifier == self.id)):
            self.connected.append(identifier)   

    def get_connections(self):
        return self.adjacent.keys()  

    def get_id(self):
        return self.id

    def get_weight(self, neighbor):
        return self.adjacent[neighbor]

    def to_JSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, 
            sort_keys=True, indent=4)

class Graph:
    def __init__(self):
        self.vert_dict = {}
        self.num_vertices = 0

    def __iter__(self):
        return iter(self.vert_dict.values())

    def add_vertex(self, node, adjacent = []):
        self.num_vertices = self.num_vertices + 1
        new_vertex = Vertex(node,adjacent)
        self.vert_dict[node] = new_vertex
        return new_vertex

    def get_vertex(self, n):
        if n in self.vert_dict:
            return self.vert_dict[n]
        else:
            return None

    def add_edge(self, frm, to, cost = 0.0):
        if frm not in self.vert_dict:
            self.add_vertex(frm)
        if to not in self.vert_dict:
            self.add_vertex(to)

        self.vert_dict[frm].add_neighbor(self.vert_dict[to], cost)
        self.vert_dict[to].add_neighbor(self.vert_dict[frm], cost)

    def get_vertices(self):
        return self.vert_dict.keys()