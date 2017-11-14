#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<math.h>
#include<time.h>
#include<sstream>
#include<queue>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<ctime>
#include<assert.h>
#include<boost/compute/detail/lru_cache.hpp>
#include<boost/optional/optional.hpp>

using namespace std;

#define FOR(i,n)  for(i=0;i<n;i++)

#define pi(n)   printf("%d\n",n);

#define ps(c)   printf("%s\n",c);

#define si(n)   scanf("%d",&n);

#define ss(n)   scanf("%s",n);

#define sf(n)   scanf("%lf",&n);

#define sc(n)   scanf(" %c",&n);

#define inf 1000000007

#define pb(a)	push_back(a)

#define FORi(i,a,n) for(i=a;i<n;i++)

#define DEBUG false

#define FAN_DEBUG false

#define LAND_DEBUG false

#define ASSERT_DEBUG false

#define RANDOM_GRAPH_PRINTING true

#define CACHE_CONSTRAINT 4


bool compare(std::pair<string, int> const &a, std::pair<string, int> const &b) {
	return (a.second != b.second? a.second > b.second : a.first > b.first);
}

//Consists of a vector of string attributes, and a string nodeId.
class Node {
public:
	std::vector<std::string> attributes;
	string nodeId;

	Node() {
	}

	Node(string nodeId) {
		this->nodeId = nodeId;
	}

	static Node emptyNode(string nodeId) {
		Node node;
		node.nodeId = nodeId;
		return node;
	}
};

//Consists of start nodeId, end nodeId, and a label for the edge between them.
class Edge {
public:
	string start;
	string end;
	string label;
	Edge(string st, string en, string la) {
		this->start = st;
		this->end = en;
		this->label = la;
	}

	Edge(int st, int en, int la) {
		this->start = std::to_string(st);
		this->end = std::to_string(en);
		this->label = std::to_string(la);
	}

	string toString() {
		std::ostringstream oss;
		oss << start << "_" << end << "_" << label;
		return oss.str();
	}
};

class Graph {
public:
	int vertexSize;
	int edgeSize;
	int labelSize;
	std::map<string, std::vector<Edge> > adjacencyList;
	std::map<string, std::vector<Edge> > revAdjacencyList;	
	map<string, Node> nodeList;
	std::vector<string> labels;

	Graph() {
	}
	//This is now correct.
	void copy(Graph g) {
		vertexSize = g.vertexSize;
		edgeSize = g.edgeSize;
		labelSize = g.labelSize;

		adjacencyList = g.adjacencyList;
		revAdjacencyList = g.revAdjacencyList;
		nodeList = g.nodeList;
		labels = g.labels;
	}

	//This is correct.
	void createNodesAndEdges(std::vector<Edge> edges, std::vector<Node> nodes, std::vector<string> labels, int vertexSize, int labelSize) {
		for (int i = 0; i < nodes.size(); i++) {
			nodeList[nodes[i].nodeId] = nodes[i];
			std::vector<Edge> v;
			adjacencyList[nodes[i].nodeId] = v;
			revAdjacencyList[nodes[i].nodeId] = v;
		}
		//cout << "Nodes initialized" << endl;
		for(int i = 0; i < edges.size();i++) {
			Edge currentEdge = edges[i];
			// if (DEBUG) {
			// 	cout << "Adjacency list size for " << currentEdge.start << " is " << (adjacencyList.find(currentEdge.start)->second).size() << endl;
			// }
			if (adjacencyList.find(currentEdge.start) == adjacencyList.end()) {
				std::vector<Edge> v;
				v.push_back(currentEdge);
				adjacencyList[currentEdge.start] = v;
			} else {
				std::vector<Edge> v = adjacencyList.find(currentEdge.start)->second;
				v.push_back(currentEdge);
				adjacencyList[currentEdge.start] = v;
			}
			// if (DEBUG) {
			// 	cout << "Adjacency list size for " << currentEdge.start << " is " << (adjacencyList.find(currentEdge.start)->second).size() << endl;
			// }
			Edge modifiedEdge = Edge(currentEdge.end, currentEdge.start, currentEdge.label);
			if (revAdjacencyList.find(modifiedEdge.start) == revAdjacencyList.end()) {
				std::vector<Edge> v;
				v.push_back(modifiedEdge);
				revAdjacencyList[modifiedEdge.start] = v;
			} else {
				std::vector<Edge> v = revAdjacencyList.find(modifiedEdge.start)->second;
				v.push_back(modifiedEdge);
				revAdjacencyList[modifiedEdge.start] = v;
			}
		}
		//cout << "Edges initialized" << endl;
		edgeSize = edges.size();
		this->vertexSize = vertexSize;
		this->labelSize = labelSize;
		this->labels = labels;
		if (DEBUG) {
			cout << labels.size() << endl;
			for(int i = 0; i < labels.size(); i++) {
				cout << labels[i] << endl;
			}

		}
	}
	/*
		The vector of nodes is an optional parameter which may or may not be passed depending on whether there are attributes which need to be
		checked.
	*/
	Graph(std::vector<Edge> edges, std::vector<Node> nodes, std::vector<string> labels, int vertexSize, int labelSize) {
		if (DEBUG) {
			cout << "Debug values to check if nodes and edges are taken in correctly" << endl;
			cout << "Nodes are as follows" << endl; 
			for(int i = 0; i < nodes.size(); i++) {
				cout << nodes[i].nodeId << endl;
			}
			cout << "Edges are as follows" << endl;
			for(int i = 0; i < edges.size();i++) {
				cout << edges[i].start << endl;
				cout << edges[i].end << endl;
				cout << edges[i].label << endl; 
			}
			cout << "Labels are as follows" << endl;
			for(int i = 0; i < labels.size(); i++) {
				cout << labels[i] << endl;
			}
			cout << "Vertex size is " << vertexSize << endl;
			cout << "Label size is " << labelSize << endl;
		}
		createNodesAndEdges(edges, nodes, labels, vertexSize, labelSize);
	}

	//This is correct
	void printGraphEdges() {
		for (map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
			std::vector<Edge> edges = (adjacencyList.find(it->first))->second;
			for(int i = 0; i < edges.size(); i++) {
				cout << "Start = " << edges[i].start << ", End = " << edges[i].end << ", Label = " << edges[i].label << endl;
			}
		}
	}

	Node getNode(string nodeId) {
		if (nodeList.find(nodeId) != nodeList.end()) {
			return nodeList.find(nodeId)->second;
		}
		if (ASSERT_DEBUG) {
			cout << "Node not found for " << nodeId;
			assert(false);
		}
		return Node::emptyNode(nodeId);
	}

	std::vector<Edge> getReverseEdges(string nodeId) {
		if (revAdjacencyList.find(nodeId) != revAdjacencyList.end()) {
			return revAdjacencyList.find(nodeId)->second;
		}
		std::vector<Edge> v;
		return v;
	}

	std::vector<Edge> getEdges(string nodeId) {
		if (adjacencyList.find(nodeId) != adjacencyList.end()) {
			return adjacencyList.find(nodeId)->second;
		}
		if (ASSERT_DEBUG) {
			cout << "AdjacencyList not found for " << nodeId;
			assert(false);
		}
		std::vector<Edge> v;
		return v;
	}

	//Should be correct.
	int findBfsDistance(string start, string end, string label) {
		if (FAN_DEBUG) {
			cout << "The query value in fan graph is " << start << " " << end << " " << label << endl;
		}
		if (start == end) {
			return 0;
		}

		std::map<string, int> nodeDist;
		std::map<string, int> revNodeDist;
		

		queue<string> q;
		q.push(start);
		nodeDist[start] = 0;

		queue<string> revQ;
		revQ.push(end);
		revNodeDist[end] = 0;

		while((!q.empty()) && (!revQ.empty())) {
			if (FAN_DEBUG) {
				cout << "Front queue size " << q.size() << " Back queue size " << revQ.size() << endl;
			}
			string front = q.front();
			q.pop();
			std::vector<Edge> frontEdges = getEdges(front);
			if (FAN_DEBUG) {
				cout << "Front is " << front << endl;
			}
			if (frontEdges.size() != 0) {
				for(int i = 0; i < frontEdges.size(); i++) {
					if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
						continue;
					}
					if (FAN_DEBUG) {
						cout << "Next vertex from front with correct label is " << frontEdges[i].end << endl; 
					}
					nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
					if (frontEdges[i].end == end) {
						return nodeDist[frontEdges[i].end];
					}
					if (revNodeDist.find(frontEdges[i].end) != revNodeDist.end()) {
						return (revNodeDist[frontEdges[i].end] + nodeDist[frontEdges[i].end]);
					}
					q.push(frontEdges[i].end);
				}
			}
			string back = revQ.front();
			revQ.pop();
			std::vector<Edge> backEdges = getReverseEdges(back);
			if (FAN_DEBUG) {
				cout << "Back is " << back << endl;
			}
			if (backEdges.size() != 0) {
				for(int i = 0; i < backEdges.size();i++) {
					if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
						continue;
					}
					if (FAN_DEBUG) {
						cout << "Next vertex from back with correct label is " << backEdges[i].end << endl; 
					}
					revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
					if (backEdges[i].end == start) {
						return revNodeDist[backEdges[i].end];
					}
					if (nodeDist.find(backEdges[i].end) != nodeDist.end()) {
						return (nodeDist[backEdges[i].end] + revNodeDist[backEdges[i].end]);
					}
					revQ.push(backEdges[i].end);
				}
			}
		}
		while (!q.empty()) {
			
			if (FAN_DEBUG) {
				cout << "Front queue size " << q.size() << endl;
			}
			string front = q.front();
			if (FAN_DEBUG) {
				cout << "Front is " << front << endl;
			}
			q.pop();
			std::vector<Edge> frontEdges = getEdges(front);
			if (frontEdges.size() != 0) {
				for(int i = 0; i < frontEdges.size(); i++) {
					if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
						continue;
					}
					nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
					if (frontEdges[i].end == end) {
						return nodeDist[frontEdges[i].end];
					}
					if (revNodeDist.find(frontEdges[i].end) != revNodeDist.end()) {
						return (revNodeDist[frontEdges[i].end] + nodeDist[frontEdges[i].end]);
					}
					q.push(frontEdges[i].end);
				}
			}
		}
		while (!revQ.empty()) {
			if (FAN_DEBUG) {
				cout << "Back queue size " << revQ.size() << endl;
			}
			string back = revQ.front();
			if (FAN_DEBUG) {
				cout << "Back is " << back << endl;
			}
			revQ.pop();
			std::vector<Edge> backEdges = getReverseEdges(back);
			if (backEdges.size() != 0) {
				for(int i = 0; i < backEdges.size();i++) {
					if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
						continue;
					}
					revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
					if (backEdges[i].end == start) {
						return revNodeDist[backEdges[i].end];
					}
					if (nodeDist.find(backEdges[i].end) != nodeDist.end()) {
						return (nodeDist[backEdges[i].end] + revNodeDist[backEdges[i].end]);
					}
					revQ.push(backEdges[i].end);
				}
			}
		}
		if (nodeDist.find(end) == nodeDist.end()) {
			return inf;
		}
		return nodeDist[end];
	}

	bool isReachable(string start, string end, string label, int distance) {
		return (findBfsDistance(start, end, label) <= distance);
	}
};

class LandmarkGraph: public Graph {
public:
	map<string, map<string, map<string, int> > > landmarkReachable;
	map<string, map<string, map<string, int> > > reverseLandmarkReachable;
	int numberOfLandmarks;
	//Hack for landmarks for now, will change to set later. 
	std::set<string> landmark;
	//std::set<string> reverseLandmark;
	int numLandmarks() {
		return CACHE_CONSTRAINT;
	}

	void allBfs(string start) {
		map<string, map<string, int> > singleLandmark;
		//Initialization, label first, then vertex.
		map<string, int> landmarkForLabel;
		for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
			landmarkForLabel[it->first] = inf;
		}
		for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
			singleLandmark[labels[labelIndex]] = landmarkForLabel;
		}
		landmarkReachable[start] = singleLandmark;
		//Actual bfs code.
		//cout << labels.size() << endl;
		
		for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
			bfs(start, labels[labelIndex]);
		}
		if (LAND_DEBUG) {
			cout << "All  bfs" << endl;
			for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
				for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
					cout << " Start = " << start << " Label = " << labels[labelIndex] << " End = " << it->first << " Distance = " << landmarkReachable[start][labels[labelIndex]][it->first] << endl;
				}
			}
		}
	}

	void allRevBfs(string start) {
		map<string, map<string, int> > singleLandmark;
		//Initialization, label first, then vertex.
		
		for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
			map<string, int> landmarkForLabel;
			for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
				landmarkForLabel[it->first] = inf;
			}
			singleLandmark[labels[labelIndex]] = landmarkForLabel;
		}
		
		for (int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
			singleLandmark[labels[labelIndex]][start] = 0;
		}
		reverseLandmarkReachable[start] = singleLandmark;
		//Actual bfs code.
		for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
			revBfs(start, labels[labelIndex]);
		}
		if (LAND_DEBUG) {
			cout << "All rev bfs" << endl;
			for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
				for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
					cout << " Start = " << start << " Label = " << labels[labelIndex] << " End = " << it->first << " Distance = " << reverseLandmarkReachable[start][labels[labelIndex]][it->first] << endl;
				}
			}
		}
	}

	void revBfs(string start, string label) {
		reverseLandmarkReachable[start][label][start] = 0;
		queue<string> bfsQueue;
		bfsQueue.push(start);
		while (!bfsQueue.empty()) {
			string front = bfsQueue.front();
			// if (DEBUG) {
			// 	cout << "Front = " << front << endl;
			// }
			bfsQueue.pop();
			std::vector<Edge> edges = getReverseEdges(front);
			for (int i = 0; i < edges.size(); i++) {
				Edge e = edges[i];
				if ((reverseLandmarkReachable[start][label][e.end] != inf) || (e.label != label)) {
					continue;
				}
				reverseLandmarkReachable[start][label][e.end] = reverseLandmarkReachable[start][label][front] + 1;
				bfsQueue.push(e.end);
			}
		}
	}

	void bfs(string start, string label) {
		landmarkReachable[start][label][start] = 0;
		queue<string> bfsQueue;
		bfsQueue.push(start);
		while (!bfsQueue.empty()) {
			string front = bfsQueue.front();
			// if (DEBUG) {
			// 	cout << "Front = " << front << endl;
			// }
			bfsQueue.pop();
			std::vector<Edge> edges = getEdges(front);
			for (int i = 0; i < edges.size(); i++) {
				Edge e = edges[i];
				if ((landmarkReachable[start][label][e.end] != inf) || (e.label != label)) {
					continue;
				}
				landmarkReachable[start][label][e.end] = landmarkReachable[start][label][front] + 1;
				bfsQueue.push(e.end);
			}
		}
	}

	bool isReachable(string start, string end, string label, int distance) {
		if (LAND_DEBUG) {
			cout << "Values of params are " << start << " " << end << " " << label << endl;
		}

		if (start == end) {
			return true;
		}
		if (isLandmarkVertex(start)) {
			if (LAND_DEBUG) {
				cout << start << " is landmark vertex, distance is " << landmarkReachable[start][label][end] << endl;
			}
			return (landmarkReachable[start][label][end] <= distance);
		}
		if (isReverseLandmarkVertex(end)) {
			if (LAND_DEBUG) {
				cout << end << " is landmark vertex, distance is " << reverseLandmarkReachable[end][label][start] << endl;
			}
			return (reverseLandmarkReachable[end][label][start] <= distance);
		}
		map<string, int> nodeDist;
		map<string, int> revNodeDist;

		queue<string> q;
		q.push(start);
		nodeDist[start] = 0;

		queue<string> revQ;
		revQ.push(end);
		revNodeDist[end] = 0;

		while (!q.empty() && !revQ.empty()) {
			string front = q.front();
			if (LAND_DEBUG) {
				cout << "Front is " << front << endl;
			}
			q.pop();
			std::vector<Edge> frontEdges = getEdges(front);
			for(int i = 0; i < frontEdges.size(); i++) {
				if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
					continue;
				}
				nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
				if (frontEdges[i].end == end) {
					return (nodeDist[end] <= distance);
				}
				if (revNodeDist.find(frontEdges[i].end) != revNodeDist.end()) {
					return ((nodeDist[frontEdges[i].end] + revNodeDist[frontEdges[i].end]) <= distance);
				}
				if (isLandmarkVertex(frontEdges[i].end)) {
					if ((landmarkReachable[frontEdges[i].end][label][end] + nodeDist[frontEdges[i].end]) <= distance) {
						return true;
					}
				}
				q.push(frontEdges[i].end);
			}

			string back = revQ.front();
			if (LAND_DEBUG) {
				cout << "Back is " << back << endl;
			}
			revQ.pop();
			std::vector<Edge> backEdges = getReverseEdges(back);
			for(int i = 0; i < backEdges.size(); i++) {
				if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
					continue;
				}
				revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
				if (backEdges[i].end == start) {
					return (revNodeDist[end] <= distance);
				}
				if (nodeDist.find(backEdges[i].end) != nodeDist.end()) {
					return ((revNodeDist[backEdges[i].end] + nodeDist[backEdges[i].end]) <= distance);
				}
				if (isReverseLandmarkVertex(backEdges[i].end)) {
					if ((reverseLandmarkReachable[backEdges[i].end][label][start] + revNodeDist[backEdges[i].end]) <= distance) {
						return true;
					}
				}
				revQ.push(backEdges[i].end);
			}
		}
		while (!q.empty()) {
			string front = q.front();
			if (LAND_DEBUG) {
				cout << "Front is " << front << endl;
			}
			q.pop();
			std::vector<Edge> frontEdges = getEdges(front);
			for(int i = 0; i < frontEdges.size(); i++) {
				if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
					continue;
				}
				nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
				if (frontEdges[i].end == end) {
					return (nodeDist[end] <= distance);
				}
				if (revNodeDist.find(frontEdges[i].end) != revNodeDist.end()) {
					return ((nodeDist[frontEdges[i].end] + revNodeDist[frontEdges[i].end]) <= distance);
				}
				if (isLandmarkVertex(frontEdges[i].end)) {
					if ((landmarkReachable[frontEdges[i].end][label][end] + nodeDist[frontEdges[i].end]) <= distance) {
						return true;
					}
				}
				q.push(frontEdges[i].end);
			}

		}
		while (!revQ.empty()) {
			string back = revQ.front();
			if (LAND_DEBUG) {
				cout << "Back is " << back << endl;
			}
			revQ.pop();
			std::vector<Edge> backEdges = getReverseEdges(back);
			for(int i = 0; i < backEdges.size(); i++) {
				if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
					continue;
				}
				revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
				if (backEdges[i].end == start) {
					return (revNodeDist[end] <= distance);
				}
				if (nodeDist.find(backEdges[i].end) != nodeDist.end()) {
					return ((revNodeDist[backEdges[i].end] + nodeDist[backEdges[i].end]) <= distance);
				}
				if (isReverseLandmarkVertex(backEdges[i].end)) {
					if ((reverseLandmarkReachable[backEdges[i].end][label][start] + revNodeDist[backEdges[i].end]) <= distance) {
						return true;
					}
				}
				revQ.push(backEdges[i].end);
			}
		}

		if (nodeDist.find(end) == nodeDist.end()) {
			if (revNodeDist.find(start) == revNodeDist.end()) {
				return false;
			} else {
				return (revNodeDist.find(start)->second <= distance);
			}
		}
		return (nodeDist[end] <= distance);
	}

	// bool isReachable(string start, string end, string label, int distance) {
	// 	if (DEBUG) {
	// 		cout << "LG Reachable Start = " << start << endl;
	// 	}
	// 	if (start == end) {
	// 		return true;
	// 	}
	// 	if (isLandmarkVertex(start)) {
	// 		return (landmarkReachable[start][label][end] <= distance);
	// 	}
	// 	if (isReverseLandmarkVertex(end)) {
	// 		return (reverseLandmarkReachable[end][label][start] <= distance);
	// 	}
	// 	map<string, int> nodeDist;
	// 	std::map<string, int> revNodeDist;
		

	// 	queue<string> q;
	// 	q.push(start);
	// 	nodeDist[start] = 0;

	// 	queue<string> revQ;
	// 	revQ.push(end);
	// 	revNodeDist[end] = 0;

	// 	while((!q.empty()) && (!revQ.empty())) {
	// 		string front = q.front();
	// 		q.pop();
	// 		std::vector<Edge> frontEdges = getEdges(front);
	// 		for(int i = 0; i < frontEdges.size(); i++) {
	// 			if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
	// 				continue;
	// 			}
	// 			nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
	// 			if (frontEdges[i].end == end) {
	// 				return (nodeDist[end] <= distance);
	// 			}
	// 			if (isLandmarkVertex(frontEdges[i].end)) {
	// 				if ((landmarkReachable[frontEdges[i].end][label][end] + nodeDist[frontEdges[i].end]) <= distance) {
	// 					return true;
	// 				}
	// 			}
	// 			q.push(frontEdges[i].end);
	// 		}

	// 		string back = revQ.front();
	// 		revQ.pop();
	// 		std::vector<Edge> backEdges = getReverseEdges(back);
	// 		for(int i = 0; i < backEdges.size(); i++) {
	// 			if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
	// 				continue;
	// 			}
	// 			revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
	// 			if (backEdges[i].end == start) {
	// 				return (revNodeDist[start] <= distance);
	// 			}
	// 			if (isReverseLandmarkVertex(backEdges[i].end)) {
	// 				if ((reverseLandmarkReachable[backEdges[i].end][label][start] + revNodeDist[backEdges[i].end]) <= distance) {
	// 					return true;
	// 				}
	// 			}
	// 			revQ.push(backEdges[i].end);
	// 		}
	// 	}
	// 	while (!q.empty()) {
	// 		string front = q.front();
	// 		q.pop();
	// 		// if (DEBUG) {
	// 		// 	cout << "LG Front = " << front << endl; 
	// 		// }
	// 		std::vector<Edge> frontEdges = getEdges(front);
	// 		// if (DEBUG) {
	// 		// 	cout << "Edge size = " << frontEdges.size() << endl;
	// 		// }
	// 		for(int i = 0; i < frontEdges.size(); i++) {
	// 			if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
	// 				continue;
	// 			}
	// 			nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
	// 			if (frontEdges[i].end == end) {
	// 				return (nodeDist[end] <= distance);
	// 			}
	// 			if (revNodeDist.find(frontEdges[i].end) != revNodeDist.end()) {
	// 				return ((nodeDist[frontEdges[i].end] + revNodeDist[frontEdges[i].end]) <= distance);
	// 			}
	// 			if (isLandmarkVertex(frontEdges[i].end)) {
	// 				if ((landmarkReachable[frontEdges[i].end][label][end] + nodeDist[frontEdges[i].end]) <= distance) {
	// 					return true;
	// 				}
	// 			}
	// 			q.push(frontEdges[i].end);
	// 		}
	// 	}
	// 	while (!revQ.empty()) {
	// 		string back = revQ.front();
	// 		revQ.pop();
	// 		std::vector<Edge> backEdges = getReverseEdges(back);
	// 		for(int i = 0; i < backEdges.size(); i++) {
	// 			if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
	// 				continue;
	// 			}
	// 			revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
	// 			if (backEdges[i].end == start) {
	// 				return (revNodeDist[start] <= distance);
	// 			}
	// 			if (nodeDist.find(backEdges[i].end) != nodeDist.end()) {
	// 				return ((nodeDist[backEdges[i].end] + revNodeDist[backEdges[i].end]) <= distance);
	// 			}
	// 			if (isReverseLandmarkVertex(backEdges[i].end)) {
	// 				if ((reverseLandmarkReachable[backEdges[i].end][label][start] + revNodeDist[backEdges[i].end]) <= distance) {
	// 					return true;
	// 				}
	// 			}
	// 			revQ.push(backEdges[i].end);
	// 		}
	// 	}
	// 	return (nodeDist[end] <= distance);
	// }

	bool isLandmarkVertex(string start) {
		if (landmark.find(start) != landmark.end()) {
			return true;
		}
		return false;
	}

	bool isReverseLandmarkVertex(string start) {
		if (landmark.find(start) != landmark.end()) {
			return true;
		}
		return false;
	}

	void initializeLandmarkVertices() {
		std::vector<pair<string, int> > vertexDegree;
		for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end();it++) {
			vertexDegree.push_back(std::make_pair(it->first, adjacencyList[it->first].size() + revAdjacencyList[it->first].size()));
		}
		std::sort(vertexDegree.begin(), vertexDegree.end(), compare);
		// if (DEBUG) {
		// 	for(int i = 0; i < vertexDegree.size(); i++) {
		// 		cout << "Landmark vertices and their sizes " << vertexDegree[i].first << " " << vertexDegree[i].second << endl;
		// 	}
		// }
		for(int i = 0; i < numberOfLandmarks; i++) {
			landmark.insert(vertexDegree[i].first);
		}

		if (LAND_DEBUG) { 
			for(std::set<string>::iterator it = landmark.begin(); it != landmark.end(); it++) {
				cout << "Landmark is " << *it << endl;
			}
		}
	}

	LandmarkGraph(Graph g) {
		copy(g);
		numberOfLandmarks = numLandmarks();
		initializeLandmarkVertices();
		if (LAND_DEBUG) {
			cout << "Initializing landmark graph" << endl;
		}
		//initializeReverseLandmarkVertices();

		for (std::set<string>::iterator it = landmark.begin(); it != landmark.end(); it++) {
			if (LAND_DEBUG) {
				cout << "Performing init" << endl;
			}
			allBfs(*it);
		}

		for (std::set<string>::iterator it = landmark.begin(); it != landmark.end(); it++) {
			if (LAND_DEBUG) {
				cout << "Performing reverse init" << endl;
			}
			allRevBfs(*it);
		}
	}
};

class FanGraph: public Graph {
public:

	boost::compute::detail::lru_cache<string, int> *cache;
	FanGraph(Graph g) {
		copy(g);
		cache = new boost::compute::detail::lru_cache<string, int>(getCacheSize());
	}
	int getCacheSize() {
		return (2*CACHE_CONSTRAINT * vertexSize * labelSize);
	}

	//Assume for now that the method doing the modification in LRU cache is present, 
	bool isReachable(string start, string end, string label, int distance) {
		string s = start + "_" + label + "_" + end;
		//string revS = end + "_" + label + "_" + start;
		// if (DEBUG) {
		// 	cout << s << endl;
		// }
		boost::optional<int> val = cache->get(s);
		//boost::optional<int> revVal = cache->get(revS);
		if (val) {
			if (DEBUG) {
				cout << "Cache hit" << endl;
			}
			int value = val.get();
			return value <= distance;
		} 
		// else if (revVal) {
		// 	int value = revVal.get();
		// 	return value <= distance;
		// } 
		else {
			int value = findBfsDistance(start, end, label);
			if (FAN_DEBUG) {
				cout << "Distance for fan graph is " << value << endl;
			}
			cache->insert(s, value);
			return (value <= distance);
		}
	}
};

/**This is a utility class, which is stateless**/
//Used only for building a random graph with certain edge labels.
class RandomGraph {
public:
	static Graph buildRandomGraph(int numVertices, int numLabels) {
		//Prob Factor 0.1
		std::vector<Edge> edges;
		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				if (i == j) {
					continue;
				}
				float prob = ((float)rand())/((float)RAND_MAX);
				if (prob < 0.005) {
					int label = (rand()%numLabels);
					edges.push_back(Edge(std::to_string(i), std::to_string(j), std::to_string(label)));
					if (DEBUG) {
						cout << i << " " << j << " " << label << endl;
					}
				}
			}
		}
		printf("Vertices = %d, Edges = %lu, Labels = %d\n", numVertices, edges.size(), numLabels);
		printf("Building random graphs\n");
		cout << numVertices << endl;
		cout << edges.size() << endl;
		cout << numLabels << endl;
		std::vector<Node> nodes;
		for(int i = 0; i < numVertices; i++) {
			Node temp = Node(std::to_string(i));
			nodes.push_back(temp);
			if (RANDOM_GRAPH_PRINTING) {
				cout << std::to_string(i) << endl;
			}
		}
		std::vector<string> labels;
		for (int i = 0; i < numLabels; i++) {
			labels.push_back(std::to_string(i));
			if (RANDOM_GRAPH_PRINTING) {
				cout << std::to_string(i) << endl;
			}
		}
		if (RANDOM_GRAPH_PRINTING) {
			for(int i = 0; i < edges.size(); i++) {
				Edge e = edges[i];
				cout << e.start << endl;
				cout << e.end << endl;
				cout << e.label << endl;
			}
		}
		Graph g = Graph(edges, nodes, labels, numVertices, numLabels);
		return g;	
	}
};

string **generateRandomQueries(Graph g, int numQueries) {
	std::vector<string> nodeIds;
	map<string, Node> nodeList = g.nodeList;
	for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		nodeIds.push_back(it->first);
	}
	int vertexSize = g.vertexSize;
	int labelSize = g.labelSize;
	int tries = 0;
	string **queries = new string*[numQueries];
	for (int i = 0; i < numQueries; i++) {
		queries[i] = new string[4];
		int start = rand()%vertexSize;
		int end = rand()%vertexSize;
		int label = rand()%labelSize;
		int distance = (rand()%(vertexSize-1))+1;
		queries[i][0] = nodeIds[start];
		queries[i][1] = nodeIds[end];
		queries[i][2] = g.labels[label];
		queries[i][3] = std::to_string(distance);
		cout << queries[i][0] << endl;
		cout << queries[i][1] << endl;
		cout << queries[i][2] << endl;
		cout << queries[i][3] << endl;
	}
	return queries;
}

Graph getGraph(int randomGraph) {
	if (randomGraph > 0) {
		return RandomGraph::buildRandomGraph(4000, 5);
	} else {
		printf("Enter number of vertices, labels, and edges\n");
		int numVertices, numLabels, numEdges;
		scanf("%d", &numVertices);
		scanf("%d",&numLabels);
		scanf("%d",&numEdges);
		std::vector<Edge> edges;
		std::vector<Node> nodes;
		std::vector<string> labels;
		if (DEBUG) {
			cout << numVertices << " " << numLabels << " " << numEdges << endl;
		}
		printf("Enter all vertices\n");
		for(int i = 0; i < numVertices; i++) {
			string curr;
			std::getline(std::cin, curr);
			if (curr == "") {
				std::getline(std::cin, curr);
			}
			if (DEBUG) {
				cout << curr << endl;
			}
			Node temp(curr);
			nodes.push_back(temp);
		}
		if (DEBUG) {
			cout << "Node size is " << nodes.size() << endl;
		}
		printf("Enter all labels\n");
		for(int i = 0; i < numLabels; i++) {
			string curr;
			std::getline(std::cin, curr);
			labels.push_back(curr);
		}
		if (DEBUG) {
			cout << "Label size is" << labels.size() << endl;
		}
		printf("Enter all edges in start end label format\n");
		for(int i = 0; i < numEdges; i++) {
			string start, end, label;
			std::getline(std::cin, start);
			std::getline(std::cin, end);
			std::getline(std::cin, label);
			//cin >> start >> end >> label;
			Edge temp(start, end, label);
			edges.push_back(temp);
		}
		if (DEBUG) {
			printf("All edges entered, seg fault is in graph creation");
		}
		return Graph(edges, nodes, labels, numVertices, numLabels);
	}
}

int main() {
	srand(time(NULL));
	int randomGraph, randomQueries;
	printf("Enter 1 if timing to be done on random graph, 0 for graph given by user");
	scanf("%d", &randomGraph);
	printf("Enter 1 if timing to be done on random queries, 0 if you will be giving queries yourself\n");
	scanf("%d", &randomQueries);
	int numQueries;
	printf("Enter number of queries to be done\n");
	scanf("%d", &numQueries);
	Graph g = getGraph(randomGraph);
	LandmarkGraph lg = LandmarkGraph(g);
	FanGraph fg = FanGraph(g);

	if (randomQueries == 1) {
		string **queries = generateRandomQueries(g, numQueries);
		clock_t lgStart = clock();
		for(int i = 0; i < numQueries; i++) {
			//cout << "Query is " << queries[i][0] <<" " << queries[i][1] << " " << queries[i][2] << " " << queries[i][3] << endl; 
			bool lgReachable =  lg.isReachable(queries[i][0],queries[i][1],queries[i][2],stoi(queries[i][3]));
		}
		clock_t lgEnd = clock();
		printf("Time taken for new algo = %lf\n", (double)(lgEnd - lgStart)/(double)(CLOCKS_PER_SEC));

		clock_t fgStart = clock();
		for(int i = 0; i < numQueries; i++) {
			//cout << "Query is " << queries[i][0] <<" " << queries[i][1] << " " << queries[i][2] << " " << queries[i][3] << endl; 
			bool fgReachable =  fg.isReachable(queries[i][0],queries[i][1],queries[i][2],stoi(queries[i][3]));
		}
		clock_t fgEnd = clock();
		printf("Time taken for old algo = %lf\n", (double)(fgEnd - fgStart)/(double)(CLOCKS_PER_SEC));
	} else if (randomQueries == 2) {
		//cout << "Reading queries from file" << endl;
		string **queries = new string*[numQueries];
		for(int i = 0; i < numQueries; i++) {
			queries[i] = new string[4];
			getline(std::cin, queries[i][0]);
			getline(std::cin, queries[i][1]);
			getline(std::cin, queries[i][2]);
			getline(std::cin, queries[i][3]);
		}
		clock_t lgStart = clock();
		for(int i = 0; i < numQueries; i++) {
			//cout << "Query is " << queries[i][0] <<" " << queries[i][1] << " " << queries[i][2] << " " << queries[i][3] << endl; 
			bool lgReachable =  lg.isReachable(queries[i][0],queries[i][1],queries[i][2],stoi(queries[i][3]));
		}
		clock_t lgEnd = clock();
		printf("Time taken for new algo = %lf\n", (double)(lgEnd - lgStart)/(double)(CLOCKS_PER_SEC));

		clock_t fgStart = clock();
		for(int i = 0; i < numQueries; i++) {
			//cout << "Query is " << queries[i][0] <<" " << queries[i][1] << " " << queries[i][2] << " " << queries[i][3] << endl; 
			bool fgReachable =  fg.isReachable(queries[i][0],queries[i][1],queries[i][2],stoi(queries[i][3]));
		}
		clock_t fgEnd = clock();
		printf("Time taken for old algo = %lf\n", (double)(fgEnd - fgStart)/(double)(CLOCKS_PER_SEC));
	} else {
		string start, end, label, distance;
		printf("Enter queries in start, end, label and distance format\n");
		for(int i = 0; i < numQueries; i++) {
			getline(std::cin, start);
			getline(std::cin, end);
			getline(std::cin, label);
			getline(std::cin, distance);
			bool lgReachable =  lg.isReachable(start, end, label, stoi(distance));
			bool fgReachable = fg.isReachable(start, end, label, stoi(distance));
			cout << "Landmark graph value is " << lgReachable << " Fan graph value is " <<  fgReachable << endl;
		}
	}



	// if (newAlgo > 0) {
	// 	LandmarkGraph lg = LandmarkGraph(g);
	// 	clock_t lgStart = clock();
	// 	for(int i = 0; i < numQueries; i++) {
	// 		bool lgReachable =  lg.isReachable(std::to_string(queries[i][0]),std::to_string(queries[i][1]),std::to_string(queries[i][2]),queries[i][3]);
	// 	}
	// 	clock_t lgEnd = clock();
	// 	printf("Time taken for new algo = %lf\n", (double)(lgEnd - lgStart));
	// } else {
	// 	FanGraph lg = FanGraph(g);
	// 	clock_t lgStart = clock();
	// 	for(int i = 0; i < numQueries; i++) {
	// 		bool lgReachable =  lg.isReachable(std::to_string(queries[i][0]),std::to_string(queries[i][1]),std::to_string(queries[i][2]),queries[i][3]);
	// 	}
	// 	clock_t lgEnd = clock();
	// 	printf("Time taken for old algo = %lf\n", (double)(lgEnd - lgStart));
	// }
	//clock_t normalEnd = clock();
	//printf("LGTime = %lf, NormalTime = %lf\n", (double)(lgEnd - lgStart), (double)(normalEnd - lgEnd));
	//printf("Random printing done.");
	//g.printGraphEdges();
}