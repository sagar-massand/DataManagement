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
#include<fstream>
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

#define NUM_LINES 58000

int main() {
	ifstream f1("gname");
	ifstream f2("gname2");
	ofstream outF("edges");
	ofstream outCompleteGraph("completeGraph");
	std::vector<pair<string, string> > edges; 
	std::set<string> mySet;
	string l1, l2;
	for(int i = 0; i < NUM_LINES; i++) {
		getline(f1, l1);
		getline(f2, l2);
		if ((l1 == "") || (l2 == "")) {
			continue;
		}
		edges.push_back(std::make_pair(l1, l2));
		mySet.insert(l1);
		mySet.insert(l2);
		outF << l1 << "\n";
		outF << l2 << "\n";
	}
	cout << "0\n0\n";
	cout << mySet.size() << endl;
	cout << "2\n";
	cout << edges.size() << endl;
	for(std::set<string>::iterator it = mySet.begin(); it != mySet.end(); it++) {
		cout << *it << "\n";
	}
	for(int i = 0; i < 2;i++) {
		cout << i << endl;
	}
	for(int i = 0; i < edges.size(); i++) {
		float prob = ((float)rand())/((float)RAND_MAX);
		if (prob < 0.8) {
			cout << edges[i].first << endl;
			cout << edges[i].second << endl;
			cout << "0" << endl;
		} else {
			cout << edges[i].first << endl;
			cout << edges[i].second << endl;
			cout << "1" << endl;
		}
	}
	return 0;
}