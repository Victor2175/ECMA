#include "stdafx.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>



class Heuristic
{
	Graph G; //The bigger graph
	Graph Gbar; //The smaller graph
	vector<int> NotInTheGraph; //Represent the set of nodes which are not in the current graph
	vector<int> NodesInGraph; //Represent the set of nodes which are in the current graph
	vector<int> Nodes;
public:

	Heuristic(Graph g, Graph gbar);
	~Heuristic();

	Graph RandomGraph();
	void SwitchNode(Graph & g,int index);
	bool IsomorphCheck(Graph & g);

};


