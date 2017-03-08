#include "stdafx.h"
#include "graph.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <list>
#include <numeric>
#include <iostream>

using namespace std;

class Heuristic
{
	Matrix * A;
	Matrix * Abar;
	int _nbDiffEdges;
	
public:

	Heuristic(Matrix * a, Matrix * abar);
	~Heuristic();

	int get_nbDiffEdges(){return _nbDiffEdges; };
	vector<int> Compute_Degrees(Matrix * m);
	Matrix * Initial_Permutation();
	Matrix * Initial_Matrix();
	int  Wrong_Indices(vector<int> degA, vector<int> degB);
	int  Good_Indices(vector<int> degA, vector<int> degB);
	void Greedy_Algorithm();
	
	void Construction_Algorithm();
	
	int objective_function(Matrix* m);

};

