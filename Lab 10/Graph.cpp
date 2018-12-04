#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <iterator>
#include "Graph.h"

Graph::Graph(ifstream &ifs) {
	int numberOfNodes;
	int numberOfEdges;

	ifs >> numberOfNodes;
	ifs >> numberOfEdges;
	ifs.ignore();

	for (int i = 0; i < numberOfNodes; ++i) {
		string label;

		getline(ifs, label);

		Vertex* v = new Vertex();
		v->label = label;
		vertices.push_back(*v);

		// Map label to vector index
		m[v->label] = i;	
	}

	// Add edges from input
	for (int j = 0; j < numberOfEdges; ++j) {
		string line;
		vector<string> edgeString;
		int vertexIndex;
		int neighborIndex;
		int cost;

		getline(ifs, line);

		size_t len = line.size();

		// get each individual word from the input
		while (len != string::npos) {
			string sub;
			len = line.find(" ");
			if (len != string::npos) {
				sub = line.substr(0, len);
				line = line.substr(len + 1, line.size());
			}
			else {
				sub = line;
			}

			edgeString.push_back(sub);
		}

		// Gives index of edgeString[0] in Graph::vertices string
		vertexIndex = m[edgeString[0]];
		neighborIndex = m[edgeString[1]];

		// Convert to integer
		cost = stoi(edgeString[2]);

		vertices[vertexIndex].neighbors.push_back(make_pair(neighborIndex, cost));
	}

	// TODO REMOVE
	//printGraph(numberOfNodes);
}

//void Graph::printGraph(int V) {
//	for (int u = 0; u < V; u++)
//	{
//		list<pair<int, int>>::iterator it;
//
//		cout << "Node " << vertices[u].label << " makes an edge with \n\n";
//
//		for (it = vertices[u].neighbors.begin(); it != vertices[u].neighbors.end(); ++it) {
//
//			cout << "  " << vertices[it->first].label << endl;
//
//			cout << "   With a cost of " << it->second << endl << endl;
//		}
//
//		cout << "--------------\n\n";
//	}
//}

void Graph::output_graph(const string &s) {
	ofstream outFS(s.c_str());

	if (!outFS.is_open()) {
		cout << "Error" << endl;
		return;
	}

	outFS << "digraph G {" << endl;
	output_graph(outFS, vertices);
	outFS << "}";
	outFS.close();

	string jpgFilename = s.substr(0, s.size() - 4) + ".jpg";
	string command = "dot -Tjpg " + s + " -o " + jpgFilename;

	system(command.c_str());
}

void Graph::output_graph(ofstream & outFS, vector<Vertex> V) {
	int size = V.size();

	list< pair<int, int> >::iterator it;

	outFS << "// nodes\n";
	for (int i = 0; i < size; i++) {
		outFS << V[i].label << " [color = pink, style = filled, label=\"key=" <<
			V[i].label << ", " << V[i].distance << "\"];\n"; 
	}
	
	outFS << "// edges\n";
	for (int j = 0; j < size; j++) {

		for (it = V[j].neighbors.begin(); it != V[j].neighbors.end(); it++) {
			outFS << V[j].label << " -> " << it->first << ";\n";
		}

	}

}

void Graph::bfs() {
	Vertex *start = &vertices[0];
	queue<Vertex*> Q;

	start->color = "GRAY";
	start->distance = 0;

	Q.push(start);

	while (!Q.empty()) {
		Vertex *currentV = Q.front();
		Q.pop();

		list< pair<int, int> >::iterator it;

		for (it = currentV->neighbors.begin(); it != currentV->neighbors.end(); ++it) {
			Vertex *adjV = &vertices[it->first];
			int cost = it->second;

			if (adjV->color == "WHITE") {
				adjV->color = "GRAY";
				adjV->distance = currentV->distance + cost;
				adjV->prev = currentV;

				Q.push(adjV);

				cout << "Pushed " << adjV->label << endl;
			}
		}

		currentV->color = "BLACK";
	}
}
