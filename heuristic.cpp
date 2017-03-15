#include "stdafx.h"
#include "heuristic.h"




//Constructor
Heuristic::Heuristic(Matrix * a,Matrix * abar)
{
	A = a;
	Abar = abar;

	_nbDiffEdges = abs(a->get_edges() - abar->get_edges());
}


//Destructor
Heuristic::~Heuristic()
{

}


//Compute the degrees of each node of a matrix
vector<int> Heuristic::Compute_Degrees(Matrix * m)
{
	vector<int> degrees;
	for(int i = 0; i < m->get_size(); i++)
	{
		int current_degree = 0;
		for(int j=0; j < m->get_size(); j++)
		{
			current_degree += m->get(i,j);
		}
		degrees.push_back(current_degree);
	}
	return degrees;
}


vector<size_t> sort_indexes(const vector<int> &v) {

  // initialize original index locations
  vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}

//The next function initialize the matrix
Matrix * Heuristic::Initial_Permutation()
{

	vector<int> DegA = Compute_Degrees(A);
	vector<int> DegAbar = Compute_Degrees(Abar);

	vector<size_t> IndicesA = sort_indexes(DegA);
	vector<size_t> IndicesAbar = sort_indexes(DegAbar);

	Matrix * res = new Matrix(A->get_size());

	for(int i=0 ; i < A->get_size() ; i++)
	{
		for(int j=0 ; j<A->get_size() ; j++)
		{
			res->set(i, j, 0);
		}
	}
	for(int i=0 ; i < A->get_size() ; i++)
	{
		res->set(IndicesA[i], IndicesAbar[i],1); 
	}
	return res;
}



Matrix * Heuristic::Initial_Matrix()
{
	Matrix * res = new Matrix(A->get_size());
	Matrix * Permutation = Initial_Permutation();

	res = Permutation->multiply(Abar);
	res = res->multiply(Permutation->transpose());
	

	return res;
}

void Heuristic::Greedy_Algorithm()
{
	srand (time(NULL));
	Matrix * B = Initial_Matrix();
	int NbIter = 10000;
	int iter =0;
	Matrix * Current_Solution = Initial_Matrix();
	
	vector<int> Permutation;
	for(int i =0; i < A->get_size(); i++)
	{
		Permutation.push_back(i);
	}
	
	vector<int> DegA = Compute_Degrees(A);
	vector<int> old_permutation = Permutation;
	int best_obj = objective_function(B);

	while(best_obj > _nbDiffEdges)
	{
		//We test a random switch on the current solution


		vector<int> DegB = Compute_Degrees(Current_Solution);
		
		int firstIndex = Wrong_Indices(DegA, DegB);
		int secondIndex = Good_Indices(DegA, DegB);

		Current_Solution->Switch_Node(firstIndex, secondIndex);
		//Current_Solution->Random_switch();

		int current_obj = objective_function(Current_Solution);
		//cout << current_obj << endl;

		if(current_obj < best_obj)
		{
			B->equalize(Current_Solution);
			best_obj = current_obj;
			cout <<best_obj << endl;
		}
		else
		{
			Current_Solution->equalize(B);
			Current_Solution->Random_switch();
		}
		iter ++;
	}
	cout << objective_function(B) << endl;
	
}


int Heuristic::Wrong_Indices(vector<int> degA, vector<int> degB)
{
	bool index_found = false;
	int index = 0;
	int i=0;
	int D = 0;
	while(index_found == false && i <(int)degA.size())
	{
		D = degA[i] - degB[i];
		if(D < 0)
		{
			index_found = true;
			index = i;
		}
		i++;
	}
	return index;
}

int Heuristic::Good_Indices(vector<int> degA, vector<int> degB)
{
	bool index_found = false;
	int index = 0;
	int i=0;
	int D = 0;
	while(index_found == false && i < (int)degA.size())
	{
		D = degA[i] - degB[i];
		if(D > 0)
		{
			index_found = true;
			index = i;
		}
		i++;
	}
	return index;
}

void Heuristic::Construction_Algorithm()
{

	bool isomorphism = false;

	//Store all degrees of A and Abar
	vector<int> degA = Compute_Degrees(A);
	vector<int> degAbar = Compute_Degrees(Abar);

	//We add initial node
	int initial_node = 0;

	vector<int> CandidatesForZero;
	for(int i =initial_node; i< A->get_size(); i++)
	{
		CandidatesForZero.push_back(i);
	}

	//This vector contains all node which are not initially in the subgraph
	vector<int> Not_In_The_Graph;
	
	//Here we fill the vector of indices (of the target) of the missing node
	for(int i=0; i < A->get_size() ; i++)
	{
		if(i != CandidatesForZero[initial_node])
		{
			Not_In_The_Graph.push_back(i);
		}
	}

	cout << "Number of candidates for the root node : " << CandidatesForZero.size() << endl;
	int nb_missing_node = (int)Not_In_The_Graph.size();

	//parent_vector contains the parent node at each node intersection
	vector<int> parent_vector;
	parent_vector.push_back(CandidatesForZero[initial_node]);


	//current_vector is the queue containing all node at specific step
	vector<int> current_vector = parent_vector;
	

	//Last_fifo 
	int last_fifo = -1;

	//Count the number of iteration
	int step =0;

	//***************************Start the loop**********************************

	//while we don't find an isomorphism
	while(isomorphism == false)
	{
		//cout << "Root node : " << CandidatesForZero[initial_node] << endl;
		//cout << "Size of parent vector : " << parent_vector.size() << endl;

		//InDepth indicates number of rejected node as candidate for the next value of phi
		//If we accept a node Indepth = 0
		int InDepth =0;
		
		//we iterate over the missing-node
		for(int idx = last_fifo+1; idx < nb_missing_node-InDepth; idx++)
		{

			//We add the next candidate
			current_vector.push_back(Not_In_The_Graph[idx]);


			if(degAbar[current_vector.size()-1] > degA[Not_In_The_Graph[idx]])
			{
				current_vector = parent_vector;
				if((int)parent_vector.size() < (int)Abar->get_size()-1)
				{
					int record_node = Not_In_The_Graph[idx];
					Not_In_The_Graph.erase(Not_In_The_Graph.begin()+idx);
					Not_In_The_Graph.push_back(record_node);
					idx = idx -1;
					InDepth +=1;
				}

			}
			else
			{
				//*********************This block is to test if the new queue is an isomorphism*************
				bool test = true;


				int last_index = (int)current_vector.size()-1;
				for(int i = 0; i < (int)current_vector.size(); i++)
				{
					if(Abar->get(i,last_index) > A->get(current_vector[i], current_vector[last_index]))
					{
						test = false;
					}
				}
				//*******************************************************************************************

				//If the function phi violates a constraint, we reject the node and push it at the back of Not_In_The_Graph
				if(test == false)
				{
					current_vector = parent_vector;
					if((int)parent_vector.size() < (int)Abar->get_size()-1)
					{
						int record_node = Not_In_The_Graph[idx];
						Not_In_The_Graph.erase(Not_In_The_Graph.begin()+idx);
						Not_In_The_Graph.push_back(record_node);
						idx = idx -1;
						InDepth +=1;
					}
				}

				//If the function phi still satisfies the constraints we add it to parent_vector and keep going on this branch
				if(test == true)
				{
					parent_vector.push_back(Not_In_The_Graph[idx]);
					last_fifo = idx;
					//last_fifo = 1;
					InDepth =0;
				}
				if(parent_vector.size() == Abar->get_size())
				{
					isomorphism = true;
					break;
				}
			}
		}
		step ++;
		//Check if the size 
		if(parent_vector.size() != Abar->get_size() && parent_vector.size() > 0)
		{
			parent_vector.pop_back();
			current_vector = parent_vector;
		}

		//We add this loop to run again the algorithm
		if(parent_vector.size() == 0)
		{
			//int initial_index = rand()%(A->get_size());
			initial_node += 1;
			if(initial_node >= (int)CandidatesForZero.size())
			{
				break;
			}
			vector<int> New;
			for(int i = 0; i < A->get_size(); i++)
			{
				if(i != CandidatesForZero[initial_node])
				{
					New.push_back(i);
				}
			}
			Not_In_The_Graph = New;

			//random_shuffle(Not_In_The_Graph.begin(), Not_In_The_Graph.end());
			parent_vector.push_back(CandidatesForZero[initial_node]);
			current_vector = parent_vector;
			nb_missing_node = (int)Not_In_The_Graph.size();
			last_fifo = -1;
		}
	}

	//In this part we juste check if effectively the graph obtained are under isomorph
	if(isomorphism == true)
	{
		cout << "The graphs are under isomorph !" << endl;
		for(int i =0; i < Abar->get_size() ; i++)
		{
			cout << "Phi(" << i << ") = " << parent_vector[i] << endl;
		}
	}
	else
	{
		cout << "Can't find an isomorphism between subgraphs !" << endl;
	}
	
}

int Heuristic::objective_function(Matrix* m)
{
	int norm = 0;
	for(int i =0; i < m->get_size() ; i++)
	{
		for(int j=i+1; j < m->get_size(); j++)
		{
			norm += abs(A->get(i,j) - m->get(i,j));
		}
	}
	return norm;

}


void Heuristic::PreProcessing()
{
	vector<int> degA = Compute_Degrees(A);
	vector<int> degAbar = Compute_Degrees(Abar);

	vector<size_t> indicesAbar = sort_indexes(degAbar);
	vector<size_t> indicesA = sort_indexes(degA);

	for(int i =0; i < degAbar.size(); i++)
	{
		Abar->Switch_Node(indicesAbar[i], degAbar.size()-1 -i);
	}
	for(int i =0; i < degA.size(); i++)
	{
		A->Switch_Node(indicesA[i], degA.size()-1 -i);
	}

}

void Heuristic::Second_Algorithm()
{
	srand(time(NULL));

	bool isomorphism = false;

	//Store all degrees of A and Abar
	vector<int> degA = Compute_Degrees(A);
	vector<int> degAbar = Compute_Degrees(Abar);

	//We add initial node
	int initial_node = 0;

	vector<int> CandidatesForZero;


	for(int i =initial_node; i< A->get_size(); i++)
	{
		if(degAbar[0] <= degA[i])
		{
			CandidatesForZero.push_back(i);
		}
	}

	//This vector contains all node which are not initially in the subgraph
	vector<int> Not_In_The_Graph;
	
	//Here we fill the vector of indices (of the target) of the missing node
	for(int i=0; i < A->get_size() ; i++)
	{
		if(i != CandidatesForZero[initial_node])
		{
			Not_In_The_Graph.push_back(i);
		}
	}
	//random_shuffle(Not_In_The_Graph.begin(), Not_In_The_Graph.end());
	
	cout << "Number of candidates for the root node : " << CandidatesForZero.size() << endl;
	cout << "Last candidate for the root node : " << CandidatesForZero[CandidatesForZero.size()-1] << endl;

	int nb_missing_node = (int)Not_In_The_Graph.size();

	//parent_vector contains the parent node at each node intersection
	vector<int> parent_vector;
	parent_vector.push_back(CandidatesForZero[initial_node]);


	//current_vector is the queue containing all node at specific step
	vector<int> current_vector = parent_vector;

	//Count the number of iteration
	int step =0;

	bool test = true;

	bool final_test = true;

	vector<int> last_guy;
	last_guy.push_back(-1);

	//***************************Start the loop**********************************

	//while we don't find an isomorphism
	while(isomorphism == false && final_test == true)
	{
		//cout << "Root node : " << CandidatesForZero[initial_node] << endl;
		//cout << "Root node : " << initial_node << endl;
		//cout << "Size of parent vector : " << parent_vector.size() << endl;
		//cout << "Last parent : " << parent_vector[parent_vector.size()-1] << endl;
		//cout << "Last guy : " << last_guy[last_guy.size()-1]<< endl;
		//cout << "test: " <<test<< endl;


		//start specifies if we go down in the tree (=-1) or if we go up 
		int start =-1;


		if(test == false)
		{			
			start = last_guy[last_guy.size()-1];
			last_guy.pop_back();
		}

		bool exit_loop = false;
		int Last_missing_node = 0;

		//we iterate over the missing-node
		for(int idx = start+1 ; idx < nb_missing_node-Last_missing_node ; idx++)
		{
			if(find(parent_vector.begin(), parent_vector.end(),Not_In_The_Graph[idx]) == parent_vector.end())
			{
				test = true;
				//We add the next candidate
				current_vector.push_back(Not_In_The_Graph[idx]);
				
				if(degAbar[current_vector.size()-1] > degA[Not_In_The_Graph[idx]])
				{
					current_vector = parent_vector;
					test = false;
				}
				else
				{
					//*********************This block is to test if the new queue is an isomorphism*************
					int last_index = (int)current_vector.size()-1;
					for(int i = 0; i < (int)current_vector.size(); i++)
					{
						if(Abar->get(i,last_index) > A->get(current_vector[i], current_vector[last_index]))
						{
							test = false;
						}
					}
					//*******************************************************************************************

					//If the function phi violates a constraint, we reject the node and push it at the back of Not_In_The_Graph
					if(test == false)
					{
						current_vector = parent_vector;
					}
					//If the function phi still satisfies the constraints we add it to parent_vector and keep going on this branch
					if(test == true)
					{
						last_guy.push_back(idx);
						parent_vector.push_back(Not_In_The_Graph[idx]);
						exit_loop = true;
						if(parent_vector.size() == Abar->get_size())
						{
							isomorphism = true;
						}
						
					}
				}
			}

			if(exit_loop == true)
			{
				break;
			}
		}
		
		

		//Check if the size 
		if(parent_vector.size() != Abar->get_size() && parent_vector.size() > 0 && test == false)
		{
			parent_vector.pop_back();
			current_vector = parent_vector;
		}

		//We add this loop to run again the algorithm
		if(parent_vector.size() == 0)
		{
			
			initial_node += 1;
			if(initial_node >= (int)CandidatesForZero.size())
			{
				final_test = false;
				break;
			}
			cout << "New Tree with root node : " << CandidatesForZero[initial_node] << endl;
			vector<int> New;
			for(int i = 0; i < A->get_size(); i++)
			{
				if(i != CandidatesForZero[initial_node])
				{
					New.push_back(i);
				}
			}
			Not_In_The_Graph = New;

			
			parent_vector.push_back(CandidatesForZero[initial_node]);
			current_vector = parent_vector;
			nb_missing_node = (int)Not_In_The_Graph.size();

			vector<int> new_last_guy;
			new_last_guy.push_back(-1);
			last_guy = new_last_guy;

			test = true;
		}
	}

	//In this part we juste check if effectively the graph obtained are under isomorph
	if(isomorphism == true)
	{
		
		cout << "The graphs are under isomorph !" << endl;
		for(int i =0; i < Abar->get_size() ; i++)
		{
			cout << "Phi(" << i << ") = " << parent_vector[i] << endl;
		}
		
	}
	else
	{
		cout << "Can't find an isomorphism between subgraphs !" << endl;
	}
	
}

