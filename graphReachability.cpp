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

#define DEBUG true

#define CACHE_CONSTRAINT 4

class Node {
public:
	std::vector<std::string> attributes;
	int nodeId;

	Node() {
	}

	static Node emptyNode(int id) {
		Node node;
		node.nodeId = id;
		return node;
	}
};

class Edge {
public:
	int start;
	int end;
	int label;
	Edge(int st, int en, int la) {
		this->start = st;
		this->end = en;
		this->label = la;
	}

	string toString() {
		std::ostringstream oss;
		oss << start << "_" << end << "_" << label;
		return oss.str();
	}

	// bool operator==(Edge& other)const{
 //        if (this->start != other.start) {
 //        	return false;
 //        }
 //        if (this->end != other.end) {
 //        	return false;
 //        }
 //        if (this->label != other.label) {
 //        	return false;
 //        }
 //        return true;
 //    }
};

class Graph {
public:
	int vertexSize;
	int edgeSize;
	set<int> nodeIds;
	map<int, std::vector<Edge> > adjacencyList;
	map<int, Node> nodeMap;

	void init() {
		vertexSize = 0;
		edgeSize = 0;
	}

	Graph() {
		init();
	}

	void copy(Graph g) {
		vertexSize = g.vertexSize;
		edgeSize = g.edgeSize;
		nodeIds = g.nodeIds;
		adjacencyList = g.adjacencyList;
		nodeMap = g.nodeMap;
	}

	void createNodesAndEdges(std::vector<Edge> edges, std::vector<Node> nodes) {
		for(int i = 0; i < edges.size();i++) {
			Edge currentEdge = edges[i];
			nodeIds.insert(currentEdge.start);
			nodeIds.insert(currentEdge.end);

			pushEdgeToAdjacencyList(currentEdge);
			Edge modifiedEdge = Edge(currentEdge.end, currentEdge.start, currentEdge.label);
			pushEdgeToAdjacencyList(modifiedEdge);
		}
		edgeSize = edges.size();
		vertexSize = nodeIds.size();
	}

	void pushEdgeToAdjacencyList(Edge currentEdge) {
		std::map<int, std::vector<Edge> >::iterator it = adjacencyList.find(currentEdge.start);
		if(it != adjacencyList.end()) {
			std::vector<Edge> v = adjacencyList.find(currentEdge.start)->second;
			v.push_back(currentEdge);
			adjacencyList[currentEdge.start] = v;
		} else {
			std::vector<Edge> v;
			v.push_back(currentEdge);
			adjacencyList[currentEdge.start] = v;
		}
	}

	/*
		The vector of nodes is an optional parameter which may or may not be passed depending on whether there are attributes which need to be
		checked.
	*/
	Graph(std::vector<Edge> edges, std::vector<Node> nodes) {
		init();
		createNodesAndEdges(edges, nodes);
	}

	void printGraphEdges() {
		set<int>::iterator it = nodeIds.begin();
		for(set<int>::iterator it = nodeIds.begin(); it != nodeIds.end(); ++it) {
			std::vector<Edge> edges = getEdges(*it);
			for (int i = 0; i < edges.size();i++) {
				printf("Start = %d, End = %d, Label = %d\n", edges[i].start, edges[i].end, edges[i].label);
			}
		}
	}

	Node getNode(int nodeId) {
		if (nodeMap.find(nodeId) != nodeMap.end()) {
			return nodeMap.find(nodeId)->second;
		}
		return Node::emptyNode(nodeId);
	}

	std::vector<Edge> getEdges(int nodeId) {
		if (adjacencyList.find(nodeId) != adjacencyList.end()) {
			return adjacencyList.find(nodeId)->second;
		}
		std::vector<Edge> v;
		return v;
	}

	int findBfsDistance(int start, int end, int label) {
		if (start == end) {
			return 0;
		}
		//For simplicity, nodes assumed
		map<int, int> nodeDist;
		for (set<int>::iterator it = nodeIds.begin();it != nodeIds.end();it++) {
			nodeDist[*it] = inf;
		}
		queue q;
		q.push(start);
		nodeDist[start] = 0;
		while (!q.empty()) {
			int front = q.front();
			std::vector<Edge> edges = getEdges(front);
			if (edges.size() == 0) {
				continue;
			}
			for (int i = 0; i < edges.size();i++) {
				if ((nodeDist[edges[i].end] == inf) || (edges[i].label != label)) {
					continue;
				}
				nodeDist[edges[i].end] = nodeDist[front] + 1;
				if (edges[i].end == end) {
					return nodeDist[edges[i].end];
				}
				q.push(edges[i].end);
			}
		}
	}

	bool isReachable(int start, int end, int label, int distance) {
		return (findBfsDistance(start, end, label) <= distance);
	}
};

class LandmarkGraph: public Graph {

}

class FanGraph: public Graph {
public:
	//Hack using string for the edge, will correct later if better solution found.
	map<string, int> reachabilityMap;
	int graphCacheConstraint;
	FanGraph(Graph g) {
		copy(g);
		graphCacheConstraint = CACHE_CONSTRAINT * vertexSize * vertexSize;
	}

	bool isReachable(int start, int end, int label, int distance) {
		Edge e = Edge(start, end, label);
		if(reachabilityMap.find(e.toString()) != reachabilityMap.end()) {
			return (reachabilityMap.find(e.toString())->second <= distance);
		} else {
			int bfsDistance = findBfsDistance(start, end, label);
			return bfsDistance <= distance;
		}
	}

	//Assume for now that the method doing the modification in LRU cache is present, 
};

/**This is a utility class, which is stateless**/
//Used only for building a random graph with certain edge labels.
class RandomGraph {
public:
	static Graph buildRandomGraph(int numVertices, int numLabels) {
		//Prob Factor 0.1
		std::vector<Edge> edges;
		for (int i = 0; i < numVertices; i++) {
			for (int j = i+1; j < numVertices; j++) {
				float prob = ((float)rand())/((float)RAND_MAX);
				if (prob < 0.1) {
					int label = (rand()%numLabels);
					edges.push_back(Edge(i, j, label));
				}
			}
		}
		std::vector<Node> nodes;
		if (DEBUG) {
			for (int j = 0; j < edges.size();j++) {
				printf("Start = %d, End = %d, Label = %d\n", edges[j].start, edges[j].end, edges[j].label);
			}
		}
		Graph g = Graph(edges, nodes);
		return g;	
	}
};

void testEdgeMap() {
	map<string, int> reachabilityMap;
	Edge e1 = Edge(1,2,3);
	Edge e2 = Edge(1,2,3);
	reachabilityMap.insert(std::pair<string, int>(e1.toString(), 10));
	std::map<string, int>::iterator it = reachabilityMap.find(e2.toString());
	if (it != reachabilityMap.end()) {
		printf("Success\n");
	} else {
		printf("Failure\n");
	}
}

void testBfs() {

}

int main() {
	//testEdgeMap();
	srand(time(NULL));
	Graph g = RandomGraph::buildRandomGraph(20, 3);
	printf("Random printing done.");
	g.printGraphEdges();
}