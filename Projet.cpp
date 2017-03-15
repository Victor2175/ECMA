// Projet.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "heuristic.h"
#include <sstream>

//#include "exo2.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));

	int si;
	int file;
	bool m_or_not;
	int NbNode;
	int NbInstance;


	cout << "Choose si* (2, 4 or 6) : " << endl;
	cin >> si;
	cout << "Choose file b0* (3, 6 or 9) : " << endl;
	cin >> file;
	cout << "Choose the number of node you want (200, 400 or 800) : " << endl; 
	cin >> NbNode;
	cout << "Which instance (between 0 and 9) : " << endl;
	cin >> NbInstance;
	
	stringstream ss0;
	ss0 << si;
	string sistar = ss0.str();

	stringstream ss4;
	ss4 << file;
	string filename = ss4.str();
	
	stringstream ss1;
	ss1 << NbNode;
	string node = ss1.str();


	stringstream ss2;
	ss2 << NbInstance;
	string instance = ss2.str();

	
	Graph Gbar("benchmarks/si"+sistar+"_bvg_b0"+ filename +"m_" + node + "/si"+sistar+"_b0"+ filename +"m_m" + node + ".0" + instance + "/pattern");
	Graph G("benchmarks/si"+sistar+"_bvg_b0"+ filename +"m_" + node + "/si"+sistar+"_b0"+ filename +"m_m" + node + ".0" + instance + "/target");
	
	
	//Graph Gbar("benchmarks/si"+sistar+"_bvg_b0"+ filename +"_" + node + "/si"+sistar+"_b0"+ filename +"_m" + node + ".0" + instance + "/pattern");
	//Graph G("benchmarks/si"+sistar+"_bvg_b0"+ filename +"_" + node + "/si"+sistar+"_b0"+ filename +"_m" + node + ".0" + instance + "/target");

	//Graph Gbar("benchmarks/si4_m4D_m4Dr6_1296/si4_m4Dr6_m1296.03/pattern");
	//Graph G("benchmarks/si4_m4D_m4Dr6_1296/si4_m4Dr6_m1296.03/target");
	//Graph Gbar("benchmarks/si6_rand_r001_200/si6_r001_m200.01/pattern");
	//Graph G("benchmarks/si6_rand_r001_200/si6_r001_m200.01/target");


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

	heuristic.Second_Algorithm();
	
	
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

