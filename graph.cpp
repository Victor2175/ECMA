#include "stdafx.h"
#include "graph.h"
#include <fstream>



Graph::Graph(string GraphName){

	readfile(GraphName);
	NbNodes = (int)AdjMatrix[0].size();
	MaxDegree = degree_max();
	cout << "Number of nodes :" << NbNodes << endl;
}

Graph::Graph(){

}

Graph::Graph(int nb){
	if(nb != 0)
	{
		NbNodes = nb;
		NbEdges = 0;
		MaxDegree = 0;
		vector<int> v(NbNodes,0);
		for(int i = 0 ; i < NbNodes; i++)
		{
			AdjMatrix.push_back(v);
		}
	}
}

Graph::Graph(Graph & G){
	if(this != &G){
		NbNodes = G.getNbNode();
		NbEdges = G.getNbEdges();
		MaxDegree = G.getMaxDegree();
		StoreAdjMatrix(G.getAdjMatrix());
	}
}


Graph::~Graph(){

}


//Operator
Graph& Graph::operator=(Graph & G){
	if(this != &G)
	{
		NbNodes = G.getNbNode();
		NbEdges = G.getNbEdges();
		StoreAdjMatrix(G.getAdjMatrix());
	}
	return *this;
}


void Graph::StoreAdjMatrix(vector<vector<int> > adjMatrix){
	int i = 0;
	for(vector<vector<int> >::iterator it = adjMatrix.begin(); it != adjMatrix.end() ; it ++){
		vector<int> v;
		for(vector<int>::iterator iter2 = (*it).begin(); iter2 != (*it).end() ; iter2 ++){
			v.push_back(*iter2);
		}
		AdjMatrix.push_back(v);
	}
}

//Function to read files and store it as graphs
void Graph::readfile(string graphName){

	string instance = "benchmarks/LV";
	vector<vector<int>> adjGbar;
	int ntarget;
	int tmp;
	int deg;

	//Lecture du fichier target
	ifstream target(instance + graphName);
	int sum = 0;
	if (target){
		target >> ntarget;
		//On va construire une matrice d'adjacence de taille ntarget X ntarget
		for (int i = 0; i<ntarget; i++){
			target >> deg;
			sum += deg;
			vector<int> v = vector<int>(ntarget,0);
			for (int j = 0; j<deg; j++){
				target >> tmp;
				v[tmp] = 1;
			}
			adjGbar.push_back(v);
		}
	}
	target.close();

	AdjMatrix = adjGbar;
	NbEdges = sum/2;
}

//Function to get the degree of a node
int Graph::degree(int index_node)
{
	int deg = 0;
	for(vector<int>::iterator it = AdjMatrix[index_node].begin() ; it != AdjMatrix[index_node].end() ; it++)
	{
		deg += *it;
	}
	return deg;
}

//Function to get the degree max
int Graph::degree_max()
{
	int deg_max = 0;
	for(int i = 0; i < NbNodes ; i++)
	{
		int current_deg = (*this).degree(i);
		if(current_deg > deg_max)
		{
			deg_max = current_deg;
		}
	}
	return deg_max;
}

vector<int> Graph::NodesDegrees(int degree)
{
	vector<int> nodes;
	for(int i = 0; i < NbNodes; i++)
	{
		int d = (*this).degree(i);
		if(d >= degree)
		{
			nodes.push_back(i);
		}
	}
	return nodes;
}



//Function to display graph
void Graph::display_graph(){
	cout << "The adjacence matrix of the graph : " << endl; 
	for (int i=0; i< NbNodes; ++i)
     {
         for (int j=0; j< NbNodes; ++j)
         {
             cout << AdjMatrix[i][j];
         }
         cout << endl;
     }
     cout << endl;

}