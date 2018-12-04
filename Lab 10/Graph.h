#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include "Vertex.h"

using namespace std;

class Graph {
private:
	vector<Vertex> vertices;

public:
	Graph();
	Graph(ifstream&);
	//~Graph();

	map<string, int> m;

	void output_graph(const string &);
	void output_graph(ofstream &, vector<Vertex>);
	void bfs();
	//void printGraph(int V);
};

#endif /* GRAPH_H_ */