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

#define ASSERT_DEBUG false

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
		nodeList = g.nodeList;
		labels = g.labels;
	}

	//This is correct.
	void createNodesAndEdges(std::vector<Edge> edges, std::vector<Node> nodes, std::vector<string> labels, int vertexSize, int labelSize) {
		for (int i = 0; i < nodes.size(); i++) {
			nodeList[nodes[i].nodeId] = nodes[i];
			std::vector<Edge> v;
			adjacencyList[nodes[i].nodeId] = v;
		}

		for(int i = 0; i < edges.size();i++) {
			Edge currentEdge = edges[i];
			// if (DEBUG) {
			// 	cout << "Adjacency list size for " << currentEdge.start << " is " << (adjacencyList.find(currentEdge.start)->second).size() << endl;
			// }
			(adjacencyList.find(currentEdge.start)->second).push_back(currentEdge);
			// if (DEBUG) {
			// 	cout << "Adjacency list size for " << currentEdge.start << " is " << (adjacencyList.find(currentEdge.start)->second).size() << endl;
			// }
			Edge modifiedEdge = Edge(currentEdge.end, currentEdge.start, currentEdge.label);
			(adjacencyList.find(modifiedEdge.start)->second).push_back(modifiedEdge);
		}
		edgeSize = edges.size();
		this->vertexSize = vertexSize;
		this->labelSize = labelSize;
	}
	/*
		The vector of nodes is an optional parameter which may or may not be passed depending on whether there are attributes which need to be
		checked.
	*/
	Graph(std::vector<Edge> edges, std::vector<Node> nodes, std::vector<string> labels, int vertexSize, int labelSize) {
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

		// while(!q.empty()) {
		// 	string front = q.front();
		// 	q.pop();
		// 	std::vector<Edge> frontEdges = getEdges(front);
		// 	if (frontEdges.size() != 0) {
		// 		for(int i = 0; i < frontEdges.size(); i++) {
		// 			if ((nodeDist[frontEdges[i].end] != inf) || (frontEdges[i].label != label)) {
		// 				continue;
		// 			}
		// 			nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
		// 			if (frontEdges[i].end == end) {
		// 				return nodeDist[frontEdges[i].end];
		// 			}
		// 			q.push(frontEdges[i].end);
		// 		}
		// 	}
		// }

		while((!q.empty()) && (!revQ.empty())) {
			if (DEBUG) {
				cout << "Front queue size " << q.size() << " Back queue size " << revQ.size() << endl;
			}
			string front = q.front();
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
			string back = revQ.front();
			revQ.pop();
			std::vector<Edge> backEdges = getEdges(back);
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
		while (!q.empty()) {
			if (DEBUG) {
				cout << "Front queue size " << q.size() << endl;
			}
			string front = q.front();
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
			if (DEBUG) {
				cout << "Back queue size " << revQ.size() << endl;
			}
			string back = revQ.front();
			revQ.pop();
			std::vector<Edge> backEdges = getEdges(back);
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
		return nodeDist[end];
	}

	bool isReachable(string start, string end, string label, int distance) {
		return (findBfsDistance(start, end, label) <= distance);
	}
};

class LandmarkGraph: public Graph {
public:
	map<string, map<string, map<string, int> > > landmarkReachable;
	int numberOfLandmarks;
	//Hack for landmarks for now, will change to set later. 
	std::set<string> landmark;
	int numLandmarks() {
		return 4;
	}

	void allBfs(string start) {
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
		landmarkReachable[start] = singleLandmark;
		//Actual bfs code.
		for(int labelIndex = 0; labelIndex < labels.size(); labelIndex++) {
			bfs(start, labels[labelIndex]);
		}
	}

	void bfs(string start, string label) {
		landmarkReachable[start][label][start] = 0;
		queue<string> bfsQueue;
		bfsQueue.push(start);
		while (!bfsQueue.empty()) {
			string front = bfsQueue.front();
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
	}

	bool isReachable(string start, string end, string label, int distance) {
		if (DEBUG) {
			cout << "LG Reachable Start = " << start << endl;
		}
		if (start == end) {
			return true;
		}
		if (isLandmarkVertex(start)) {
			return (landmarkReachable[start][label][end] <= distance);
		}
		if (isLandmarkVertex(end)) {
			return (landmarkReachable[end][label][start] <= distance);
		}
		map<string, int> nodeDist;
		std::map<string, int> revNodeDist;
		

		queue<string> q;
		q.push(start);
		nodeDist[start] = 0;

		queue<string> revQ;
		revQ.push(end);
		revNodeDist[end] = 0;

		while((!q.empty()) && (!revQ.empty())) {
			string front = q.front();
			q.pop();
			// if (DEBUG) {
			// 	cout << "LG Front = " << front << endl; 
			// }
			std::vector<Edge> frontEdges = getEdges(front);
			// if (DEBUG) {
			// 	cout << "Edge size = " << frontEdges.size() << endl;
			// }
			for(int i = 0; i < frontEdges.size(); i++) {
				if ((nodeDist.find(frontEdges[i].end) != nodeDist.end()) || (frontEdges[i].label != label)) {
					continue;
				}
				nodeDist[frontEdges[i].end] = nodeDist[front] + 1;
				if (frontEdges[i].end == end) {
					return (nodeDist[end] <= distance);
				}
				if (isLandmarkVertex(frontEdges[i].end)) {
					if ((landmarkReachable[frontEdges[i].end][label][end] + nodeDist[frontEdges[i].end]) <= distance) {
						return true;
					}
				}
				q.push(frontEdges[i].end);
			}

			string back = revQ.front();
			revQ.pop();
			std::vector<Edge> backEdges = getEdges(back);
			for(int i = 0; i < backEdges.size(); i++) {
				if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
					continue;
				}
				revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
				if (backEdges[i].end == start) {
					return (revNodeDist[start] <= distance);
				}
				if (isLandmarkVertex(backEdges[i].end)) {
					if ((landmarkReachable[backEdges[i].end][label][start] + revNodeDist[backEdges[i].end]) <= distance) {
						return true;
					}
				}
				revQ.push(backEdges[i].end);
			}
		}
		while (!q.empty()) {
			string front = q.front();
			q.pop();
			// if (DEBUG) {
			// 	cout << "LG Front = " << front << endl; 
			// }
			std::vector<Edge> frontEdges = getEdges(front);
			// if (DEBUG) {
			// 	cout << "Edge size = " << frontEdges.size() << endl;
			// }
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
			revQ.pop();
			std::vector<Edge> backEdges = getEdges(back);
			for(int i = 0; i < backEdges.size(); i++) {
				if ((revNodeDist.find(backEdges[i].end) != revNodeDist.end()) || (backEdges[i].label != label)) {
					continue;
				}
				revNodeDist[backEdges[i].end] = revNodeDist[back] + 1;
				if (backEdges[i].end == start) {
					return (revNodeDist[start] <= distance);
				}
				if (nodeDist.find(backEdges[i].end) != nodeDist.end()) {
					return ((nodeDist[backEdges[i].end] + revNodeDist[backEdges[i].end]) <= distance);
				}
				if (isLandmarkVertex(backEdges[i].end)) {
					if ((landmarkReachable[backEdges[i].end][label][start] + revNodeDist[backEdges[i].end]) <= distance) {
						return true;
					}
				}
				revQ.push(backEdges[i].end);
			}
		}
		return (nodeDist[end] <= distance);
	}

	bool isLandmarkVertex(string start) {
		std::set<string>::iterator it = landmark.find(start);
		if (it != landmark.end()) {
			return true;
		}
		return false;
	}

	void initializeLandmarkVertices() {
		std::vector<pair<string, int> > vertexDegree;
		for(map<string, Node>::iterator it = nodeList.begin(); it != nodeList.end();it++) {
			vertexDegree.push_back(std::make_pair(it->first, 2*adjacencyList[it->first].size()));
		}
		std::sort(vertexDegree.begin(), vertexDegree.end(), compare);
		if (DEBUG) {
			for(int i = 0; i < vertexDegree.size(); i++) {
				cout << "Landmark vertices and their sizes " << vertexDegree[i].first << " " << vertexDegree[i].second << endl;
			}
		}
		for(int i = 0; i < numberOfLandmarks; i++) {
			landmark.insert(vertexDegree[i].first);
		}
	}

	LandmarkGraph(Graph g) {
		copy(g);
		numberOfLandmarks = numLandmarks();
		initializeLandmarkVertices();
		//Do the indexing for all k landmarks.
		for (std::set<string>::iterator it = landmark.begin(); it != landmark.end(); it++) {
			allBfs(*it);
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
		return 4 * vertexSize;
	}

	//Assume for now that the method doing the modification in LRU cache is present, 
	bool isReachable(string start, string end, string label, int distance) {
		string s = start + "_" + label + "_" + end;
		string revS = end + "_" + label + "_" + start;
		if (DEBUG) {
			cout << s << endl;
		}
		boost::optional<int> val = cache->get(s);
		boost::optional<int> revVal = cache->get(revS);
		if (val) {
			if (DEBUG) {
				cout << "Cache hit" << endl;
			}
			int value = val.get();
			return value <= distance;
		} else if (revVal) {
			int value = revVal.get();
			return value <= distance;
		} else {
			int value = findBfsDistance(start, label, end);
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
			for (int j = i+1; j < numVertices; j++) {
				float prob = ((float)rand())/((float)RAND_MAX);
				if (prob < 0.1) {
					int label = (rand()%numLabels);
					edges.push_back(Edge(std::to_string(i), std::to_string(j), std::to_string(label)));
				}
			}
		}
		printf("Vertices = %d, Edges = %lu, Labels = %d\n", numVertices, edges.size(), numLabels);
		std::vector<Node> nodes;
		for(int i = 0; i < numVertices; i++) {
			Node temp = Node(std::to_string(i));
			nodes.push_back(temp);
		}
		std::vector<string> labels;
		for (int i = 0; i < numLabels; i++) {
			labels.push_back(std::to_string(i));
		}
		Graph g = Graph(edges, nodes, labels, numVertices, numLabels);
		return g;	
	}
};

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

Graph getGraph(int randomGraph) {
	if (randomGraph > 0) {
		return RandomGraph::buildRandomGraph(1000, 5);
	} else {
		printf("Enter number of vertices, labels, and edges\n");
		int numVertices, numLabels, numEdges;
		scanf("%d%d%d", &numVertices, &numLabels, &numEdges);
		std::vector<Edge> edges;
		std::vector<Node> nodes;
		std::vector<string> labels;
		for(int i = 0; i < numVertices; i++) {
			string curr;
			cin >> curr;
			Node temp(curr);
			nodes.push_back(temp);
		}
		for(int i = 0; i < numLabels; i++) {
			string curr;
			cin >> curr;
			labels.push_back(curr);
		}
		for(int i = 0; i < numEdges; i++) {
			string start, end, label;
			cin >> start >> end >> label;
			Edge temp(start, end, label);
			edges.push_back(temp);
		}
		return Graph(edges, nodes, labels, numVertices, numLabels);
	}
}

int main() {
	srand(time(NULL));
	int newAlgo, randomGraph;
	printf("Enter 1 if timing to be done for new algo, 0 for old algo");
	scanf("%d",&newAlgo);
	printf("Enter 1 if timing to be done on random graph, 0 for graph given by user");
	scanf("%d", &randomGraph);
	Graph g = getGraph(randomGraph);
	int numQueries = 10000;
	int **queries = generateRandomQueries(g, numQueries);
	if (newAlgo > 0) {
		LandmarkGraph lg = LandmarkGraph(g);
		clock_t lgStart = clock();
		for(int i = 0; i < numQueries; i++) {
			bool lgReachable =  lg.isReachable(std::to_string(queries[i][0]),std::to_string(queries[i][1]),std::to_string(queries[i][2]),queries[i][3]);
		}
		clock_t lgEnd = clock();
		printf("Time taken for new algo = %lf", (double)(lgEnd - lgStart));
	} else {
		FanGraph lg = FanGraph(g);
		clock_t lgStart = clock();
		for(int i = 0; i < numQueries; i++) {
			bool lgReachable =  lg.isReachable(std::to_string(queries[i][0]),std::to_string(queries[i][1]),std::to_string(queries[i][2]),queries[i][3]);
		}
		clock_t lgEnd = clock();
		printf("Time taken for old algo = %lf", (double)(lgEnd - lgStart));
	}
	//clock_t normalEnd = clock();
	//printf("LGTime = %lf, NormalTime = %lf\n", (double)(lgEnd - lgStart), (double)(normalEnd - lgEnd));
	//printf("Random printing done.");
	//g.printGraphEdges();
}