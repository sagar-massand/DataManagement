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
	//Vertices from 0 to (vertexSize - 1)
	int vertexSize;
	int edgeSize;
	int labelSize;
	std::vector<std::vector<Edge> > adjacencyList;
	std::vector<Node> nodeList;

	Graph() {
	}
	//This is now correct.
	void copy(Graph g) {
		vertexSize = g.vertexSize;
		edgeSize = g.edgeSize;
		labelSize = g.labelSize;

		adjacencyList = g.adjacencyList;
		nodeList = g.nodeList;
	}

	//This is correct.
	void createNodesAndEdges(std::vector<Edge> edges, std::vector<Node> nodes, int vertexSize, int labelSize) {
		for (int i = 0; i < vertexSize; i++) {
			std::vector<Edge> v;
			adjacencyList.push_back(v);
		}
		for(int i = 0; i < edges.size();i++) {
			Edge currentEdge = edges[i];
			adjacencyList[currentEdge.start].push_back(currentEdge);
			Edge modifiedEdge = Edge(currentEdge.end, currentEdge.start, currentEdge.label);
			adjacencyList[modifiedEdge.start].push_back(modifiedEdge);
		}
		nodeList = nodes;
		edgeSize = edges.size();
		this->vertexSize = vertexSize;
		this->labelSize = labelSize;
	}

	// void pushEdgeToAdjacencyList(Edge currentEdge) {
	// 	std::map<int, std::vector<Edge> >::iterator it = adjacencyList.find(currentEdge.start);
	// 	if(it != adjacencyList.end()) {
	// 		std::vector<Edge> v = adjacencyList.find(currentEdge.start)->second;
	// 		v.push_back(currentEdge);
	// 		adjacencyList[currentEdge.start] = v;
	// 	} else {
	// 		std::vector<Edge> v;
	// 		v.push_back(currentEdge);
	// 		adjacencyList[currentEdge.start] = v;
	// 	}
	// }

	/*
		The vector of nodes is an optional parameter which may or may not be passed depending on whether there are attributes which need to be
		checked.
	*/
	Graph(std::vector<Edge> edges, std::vector<Node> nodes, int vertexSize, int labelSize) {
		createNodesAndEdges(edges, nodes, vertexSize, labelSize);
	}

	void printGraphEdges() {
		for (int i = 0; i < adjacencyList.size(); i++) {
			for (int j = 0; j < adjacencyList[i].size();j++) {
				printf("Start = %d, End = %d, Label = %d\n", adjacencyList[i][j].start, adjacencyList[i][j].end, adjacencyList[i][j].label);
			}
		}
	}

	Node getNode(int nodeId) {
		if (nodeList.size() > nodeId) {
			return nodeList[nodeId];
		}
		return Node::emptyNode(nodeId);
	}

	std::vector<Edge> getEdges(int nodeId) {
		if (adjacencyList.size() > nodeId) {
			return adjacencyList[nodeId];
		}
		std::vector<Edge> v;
		return v;
	}

	//Should be correct.
	int findBfsDistance(int start, int end, int label) {
		if (start == end) {
			return 0;
		}
		//For simplicity, nodes assumed
		std::vector<int> nodeDist;
		for (int i = 0; i < vertexSize; i++) {
			nodeDist.push_back(inf);
		}
		queue<int> q;
		q.push(start);

		nodeDist[start] = 0;
		while (!q.empty()) {
			int front = q.front();
			q.pop();
			std::vector<Edge> edges = getEdges(front);
			if (edges.size() == 0) {
				continue;
			}
			for (int i = 0; i < edges.size();i++) {
				if ((nodeDist[edges[i].end] != inf) || (edges[i].label != label)) {
					continue;
				}
				nodeDist[edges[i].end] = nodeDist[front] + 1;
				if (edges[i].end == end) {
					return nodeDist[edges[i].end];
				}
				q.push(edges[i].end);
			}
		}
		return nodeDist[end];
	}

	bool isReachable(int start, int end, int label, int distance) {
		return (findBfsDistance(start, end, label) <= distance);
	}
};

class LandmarkGraph: public Graph {
public:
	map<int, std::vector<std::vector<int> > > landmarkReachable;
	int k;
	//Hack for landmarks for now, will change to set later. 
	int *landmark;

	void allBfs(int start) {
		std::vector<std::vector<int> > singleLandmark;
		//Initialization, label first, then vertex.
		for (int label = 0; label < labelSize; label++) {
			std::vector<int> v;
			for(int j = 0; j < vertexSize; j++) {
				v.push_back(inf);
			}
			singleLandmark.push_back(v);
		}
		for (int label = 0; label < labelSize; label++) {
			singleLandmark[label][start] = 0;
		}
		landmarkReachable[start] = singleLandmark;
		//Actual bfs code.
		for(int label = 0; label < labelSize; label++) {
			bfs(start, label);
		}
	}

	void bfs(int start, int label) {
		landmarkReachable[start][label][start] = 0;
		queue<int> bfsQueue;
		bfsQueue.push(start);
		while (!bfsQueue.empty()) {
			int front = bfsQueue.front();
			if (DEBUG) {
				cout << "Front = " << front << endl;
			}
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
		if (DEBUG) {
			for (int j = 0; j < vertexSize; j++) {
				printf("Start = %d, label = %d, end = %d, distance = %d\n", start, label, j, landmarkReachable[start][label][j]);
			}
		}
	}

	bool isReachable(int start, int end, int label, int distance) {
		if (DEBUG) {
			cout << "LG Reachable Start = " << start << endl;
		}
		if (start == end) {
			return true;
		}
		if (isLandmarkVertex(start)) {
			return (landmarkReachable[start][label][end] <= distance);
		}
		std::vector<int> nodeDist;
		for(int i = 0; i < vertexSize; i++) {
			nodeDist.push_back(inf);
		}
		queue<int> q;
		nodeDist[start] = 0;
		q.push(start);
		while(!q.empty()) {
			int front = q.front();
			q.pop();
			if (DEBUG) {
				cout << "LG Front = " << front << endl; 
			}
			std::vector<Edge> edges = getEdges(front);
			if (DEBUG) {
				cout << "Edge size = " << edges.size() << endl;
			}
			for(int i = 0; i < edges.size(); i++) {
				if ((nodeDist[edges[i].end]!=inf) || (edges[i].label != label)) {
					continue;
				}
				nodeDist[edges[i].end] = nodeDist[front] + 1;
				if (isLandmarkVertex(edges[i].end)) {
					if (landmarkReachable[edges[i].end][label][end] + nodeDist[edges[i].end] <= distance) {
						return true;
					}
				}
				q.push(edges[i].end);
			}
		}
		return (nodeDist[end] <= distance);
	}

	int isLandmarkVertex(int start) {
		for (int i = 0; i < k; i++) {
			if (start == landmark[i]) {
				return true;
			}
		}
		return false;
	}

	LandmarkGraph(Graph g) {
		copy(g);
		k = (vertexSize/20) + 1;
		//k = 5;
		landmark = new int[k];
		for(int i = 0; i < k; i++) {
			landmark[i] = -1;
		}
		std::vector<int> vertexDegree;

		//Because bidirectional edge assumption.
		for (int i = 0; i < vertexSize; i++) {
			vertexDegree.push_back(2*adjacencyList[i].size());
		}

		for (int i = 0; i < vertexDegree.size();i++) {
			int j;
			for (j = 0; j < k; j++) {
				if (landmark[j] == -1) {
					landmark[j] = i;
					break;
				}
			}
			if (j == k) {
				int argMin = 0;
				for(int w = 1; w < k; w++) {
					if (vertexDegree[landmark[argMin]] > vertexDegree[landmark[w]]) {
						argMin = w;
					}
				}
				if(vertexDegree[i] > vertexDegree[landmark[argMin]]) {
					landmark[argMin] = i;
				}
			}
		}
		// //Top k landmarks found.
		// for (map<int, int>::iterator it = vertexDegree.begin(); it != vertexDegree.end();it++) {
		// 	int i;
		// 	for(i = 0; i < k; i++) {
		// 		if (landmark[i] == -1) {
		// 			landmark[i] = it->first;
		// 			break;
		// 		}
		// 	}
		// 	if (i == k) {
		// 		int argMin = 0;
		// 		for (int j = 1; j < k;j++) {
		// 			if (vertexDegree[landmark[j]] < vertexDegree[landmark[argMin]]) {
		// 				argMin = j;
		// 			}
		// 		}
		// 		if (it->second > vertexDegree[landmark[argMin]]) {
		// 			landmark[argMin] = it->first;
		// 		}
		// 	}
		// }

		//Do the indexing for all k landmarks.
		for (int i = 0; i < k; i++) {
			allBfs(landmark[i]);
		}
	}
};

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
		printf("Vertices = %d, Edges = %lu, Labels = %d\n", numVertices, edges.size(), numLabels);
		std::vector<Node> nodes;
		if (DEBUG) {
			for (int j = 0; j < edges.size();j++) {
				printf("Start = %d, End = %d, Label = %d\n", edges[j].start, edges[j].end, edges[j].label);
			}
		}
		Graph g = Graph(edges, nodes, numVertices, numLabels);
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
	std::vector<Edge> edges;
	edges.push_back(Edge(1,2,0));
	edges.push_back(Edge(1,3,1));
	edges.push_back(Edge(2,4,0));
	edges.push_back(Edge(4,6,0));
	edges.push_back(Edge(3,5,1));
	edges.push_back(Edge(6,3,0));
	std::vector<Node> nodes;
	Graph g = Graph(edges, nodes, 7, 2);
	LandmarkGraph lg = LandmarkGraph(g);

	//Original graph
	cout << "Original graph results" << endl;
	cout << g.isReachable(1,3,0,4) << endl;
	cout << g.isReachable(1,3,1,2) << endl;
	cout << g.isReachable(1,5,0,3) << endl;
	cout << g.isReachable(2,3,0,4) << endl;

	//Landmark graph

	cout << "Landmark graph results" << endl;
	cout << lg.isReachable(1,3,0,4) << endl;
	cout << lg.isReachable(1,3,1,2) << endl;
	cout << lg.isReachable(1,5,0,3) << endl;
}

int **generateRandomQueries(Graph g, int numQueries) {
	int vertexSize = g.vertexSize;
	int labelSize = g.labelSize;
	int tries = 0;
	int **queries = new int*[numQueries];
	for (int i = 0; i < numQueries; i++) {
		queries[i] = new int[4];
		int start = rand()%(vertexSize-1);
		int end = ((rand()%(vertexSize-(start+1))) + (start + 1));
		int label = rand()%labelSize;
		int distance = rand()%vertexSize;
		queries[i][0] = start;
		queries[i][1] = end;
		queries[i][2] = label;
		queries[i][3] = distance;
	}
	return queries;
}

int main() {
	//testEdgeMap();
	//testBfs();
	srand(time(NULL));
	Graph g = RandomGraph::buildRandomGraph(1000, 5);
	LandmarkGraph lg = LandmarkGraph(g);
	int numQueries = 1000;
	int **queries = generateRandomQueries(g, numQueries);
	clock_t lgStart = clock();
	for(int i = 0; i < numQueries; i++) {
		bool lgReachable =  lg.isReachable(queries[i][0],queries[i][1],queries[i][2],queries[i][3]);
	}
	clock_t lgEnd = clock();
	for(int i = 0; i < numQueries; i++) {
		bool reachable = g.isReachable(queries[i][0],queries[i][1],queries[i][2],queries[i][3]);
	}
	clock_t normalEnd = clock();
	printf("LGTime = %lf, NormalTime = %lf\n", (double)(lgEnd - lgStart), (double)(normalEnd - lgEnd));
	//printf("Random printing done.");
	//g.printGraphEdges();
}