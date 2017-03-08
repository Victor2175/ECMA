// Projet.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "heuristic.h"
//#include "exo2.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));

	Graph Gbar("benchmarks/si2_bvg_b03_200/si2_b03_m200.03/pattern");
	
	Graph G("benchmarks/si2_bvg_b03_200/si2_b03_m200.03/target");



	//G is the greatest graph !!
	vector< vector<int> > a_ij = G.getAdjMatrix();
	vector< vector<int> > abar_ij = Gbar.getAdjMatrix();


	//******************************Here begins the code for the heuristic*********************************

	Matrix* A = new Matrix(G.getNbNode());
	Matrix* Abar = new Matrix(Gbar.getNbNode());

	A->read_from_vector(a_ij);
	Abar->read_from_vector(abar_ij);

	a_ij.clear();
	abar_ij.clear();

	Heuristic heuristic(A, Abar);

	//cout << heuristic.get_nbDiffEdges() << endl;

	clock_t t;
	t = clock();

	heuristic.Construction_Algorithm();
	
	
	t = clock() - t;

	printf ("Computation time : %f seconds.\n",((float)t)/CLOCKS_PER_SEC);
	
	//heuristic.Greedy_Algorithm();

	//InitialMatrix->display("Initial matrix");
	
	//Heuristic heuristic(G,Gbar);

	//G.display_graph();
	//Gbar.display_graph();
	/*
	vector<int> InitialPermutation0;
	vector<int> InitialPermutation1;
	for(int i = 0; i < Gbar.getNbNode() ; i++)
	{
		InitialPermutation0.push_back(i);
	}
	InitialPermutation1 = InitialPermutation0;
	Graph Gprime = heuristic.RandomGraph();
	bool a = heuristic.IsomorphCheck(Gprime, InitialPermutation0);

	InitialPermutation0 = InitialPermutation1;
	Gprime.display_graph();
	
	int NbIterMax = 10000;
	int iter = 0;
	
	while(a == false && iter < NbIterMax)
	{
		int index = rand()%(Gprime.getNbNode()-1);
		heuristic.SwitchNode(Gprime, index);
		a = heuristic.IsomorphCheck(Gprime, InitialPermutation0);
		InitialPermutation0 = InitialPermutation1;
		cout << a << endl;
		iter++;
	}
		
	Gprime.display_graph();
	if(a == 1)
	{
		cout << "The graphs are under isomorph !" << endl;
	}
	
	*/
	/*Exo2 Exercise2(G, Gbar);

	cout << "houhou" << endl;

	Exercise2.build_model();

	Exercise2.solve_model();
	*/
	return 0;
}

