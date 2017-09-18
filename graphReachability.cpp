#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<time.h>
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

	Graph(std::vector<Edge> edges) {
	}

	/*
		The vector of nodes is an optional parameter which may or may not be passed depending on whether there are attributes which need to be
		checked.
	*/
	Graph(std::vector<Edge> edges, std::vector<Node> nodes) {
		init();
		for(int i = 0; i < edges.size();i++) {
			Edge currentEdge = edges[i];
			nodeIds.insert(currentEdge.start);
			nodeIds.insert(currentEdge.end);

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

			it = adjacencyList.find(currentEdge.end);
			if(it != adjacencyList.end()) {
				std::vector<Edge> v = adjacencyList.find(currentEdge.end)->second;
				v.push_back(currentEdge);
				adjacencyList[currentEdge.end] = v;
			} else {
				std::vector<Edge> v;
				v.push_back(currentEdge);
				adjacencyList[currentEdge.end] = v;
			}
		}
		edgeSize = edges.size();
		vertexSize = nodeIds.size();
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
};

class FanGraph {
public:
	FanGraph(Graph g) {

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


int main() {
	srand(time(NULL));
	Graph g = RandomGraph::buildRandomGraph(20, 3);
	printf("Random printing done.");
	g.printGraphEdges();
}