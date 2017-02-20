#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Graph{
	
	int NbNodes;
	int NbEdges;
	int MaxDegree;
	vector< vector<int> > AdjMatrix;

public:

	//Constructor and destructor
	Graph();
	Graph(string GraphName);
	Graph(int nb);
	Graph(Graph & G);
	~Graph();

	//Operator
	Graph& operator=(Graph & G);

	//Get functions
	int getNbNode(){return NbNodes; };
	int getNbEdges(){return NbEdges; };
	int getMaxDegree(){return MaxDegree; };
	vector<vector<int> > getAdjMatrix(){ return AdjMatrix; };

	//Set functions 
	void setNbNode(int nb){ NbNodes = nb; };
	void setAdjMatrixElement(int position_i, int position_j, int value){ AdjMatrix[position_i][position_j] = value;};
	void setAdjMatrix(vector<vector<int> > const matrix){ AdjMatrix = matrix; };

	//Function to get the degree of a node
	int degree(int index_node);
	int degree_max();
	vector<int> NodesDegrees(int degree);

	//Store adjacence matrix
	void StoreAdjMatrix(vector<vector<int> > adjMatrix);

	//Read graph from files
	void readfile(string graphName);

	//Display graph
	void display_graph();




};






