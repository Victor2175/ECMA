// Projet.cpp : définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "heuristic.h"


int _tmain(int argc, _TCHAR* argv[])
{
	
	Graph Gbar("/g4");
	Graph G("/g5");

	Heuristic heuristic(G,Gbar);

	G.display_graph();
	//Gbar.display_graph();

	Graph Gprime = heuristic.RandomGraph();
	bool a = heuristic.IsomorphCheck(Gprime);


	int NbIterMax = 1000;
	int iter = 0;

	while(a == false && iter < NbIterMax)
	{
		int index = rand()%(Gprime.getNbNode()-1);
		heuristic.SwitchNode(Gprime, index);
		bool a = heuristic.IsomorphCheck(Gprime);
		//Gprime.display_graph();

		cout << a << endl;

		iter++;
	}
		
	Gprime.display_graph();
	if(a == 1)
	{
		cout << "The graphs are under isomorph !" << endl;
	}


	//Exo2 Exercise2(G, Gbar);

	//Exercise2.build_model();

	//Exercise2.solve_model();

	return 0;
}

