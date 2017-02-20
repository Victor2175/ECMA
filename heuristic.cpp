#include "stdafx.h"
#include "heuristic.h"




//Constructor
Heuristic::Heuristic(Graph g, Graph gbar)
{
	G = g;
	Gbar = gbar;
	NotInTheGraph = vector<int>(0);
	NodesInGraph = vector<int>(0);
	for(int i =  0; i < G.getNbNode() ; i++)
	{
		Nodes.push_back(i);
	}
}

//Destructor
Heuristic::~Heuristic()
{

}


//Create a rando graph of n node from the graph G
Graph Heuristic::RandomGraph()
{
	srand(time(NULL));
	int n = Gbar.getNbNode();

	Graph newG(n);

	vector< vector <int> > adjMatrix;
	vector<int> MixNodes = Nodes;


	//Changer cette partie là afin de rajouter le tirage sans doublon
	random_shuffle(MixNodes.begin(), MixNodes.end());

	//Add the node in the graph
	for(int i = n; i < G.getNbNode() ; i++)
	{
		NotInTheGraph.push_back(MixNodes[i]);
	}
	for(int i = 0; i < n ; i++)
	{
		NodesInGraph.push_back(MixNodes[i]);
	}


	for(int i = 0; i < n; i++)
	{
		vector<int> currNode;
		for(int j = 0; j < n ; j++)
		{
			currNode.push_back((G.getAdjMatrix())[MixNodes[i]][MixNodes[j]]);
		}
		adjMatrix.push_back(currNode);
	}
	newG.setAdjMatrix(adjMatrix);

	cout << "The random graph is created " << endl;

	return newG;
}

void Heuristic::SwitchNode(Graph & g, int index)
{
	//index is between 0 and n-1
	srand(time(NULL));

	int n = Gbar.getNbNode();
	int AddIndex =0;


	if(NotInTheGraph.size() > 1)
	{
		AddIndex = rand()%(NotInTheGraph.size()-1)+0;
	}
	else if(NotInTheGraph.size() == 0)
	{
		return;
	}

	for(int i=0; i < n ; i++)
	{
		g.setAdjMatrixElement(index, i,  G.getAdjMatrix()[NotInTheGraph[AddIndex]][NodesInGraph[i]]);
		g.setAdjMatrixElement(i, index, G.getAdjMatrix()[NodesInGraph[i]][NotInTheGraph[AddIndex]]);

		//Nodes.insert(Nodes.begin()+index+1, NotInTheGraph[AddIndex]);
		//NotInTheGraph.insert(NotInTheGraph.begin()+ AddIndex+1, Nodes[index]); 

		
		//Nodes.erase(Nodes.begin() + index);
		//NotInTheGraph.erase(NotInTheGraph.begin() + AddIndex);


		//Nodes.insert(NotInTheGraph[AddIndex]); 
	}
	

	//We update the node indices in Nodes and NotInTheGraph vector
	int record = NodesInGraph[index];
	replace(NodesInGraph.begin(), NodesInGraph.end(), NodesInGraph[index], NotInTheGraph[AddIndex]);
	replace(NotInTheGraph.begin(), NotInTheGraph.end(), NotInTheGraph[AddIndex], record);

}
	

bool Heuristic::IsomorphCheck(Graph & g)
{
	bool check = true;

	int i =0;

	while(check == true)
	{
		for(int j =0; j < g.getNbNode() ; j++) 
		{
			if(g.getAdjMatrix()[i][j] != Gbar.getAdjMatrix()[i][j])
			{
				check = false;
			}
		}
		i++;
	}
	return check;
}


