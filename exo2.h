#include "stdafx.h"
#include "graph.h"
#include "ilcplex\ilocplex.h"
#include <vector>
ILOSTLBEGIN

using namespace std;

//Define 2D arrays for variables and constraints
typedef IloArray<IloNumVarArray> NumVarArray2;
typedef IloArray<IloNumArray> NumArray2;

typedef IloArray<IloRangeArray> RangeArray2;


class Exo2{

	//The graphs
	Graph G;
	Graph Gbar;
	int Nmax;

	//The environment
    IloEnv env;
    
    //The model
    IloModel model;

	//adjacence matrix
	vector<vector<int>> a_ij;
	vector<vector<int>> abar_ij;
    
    //Variables
    NumVarArray2 x_ij;     //Define the binary variables x_ij 
    NumVarArray2 u_ij;      //Define the binary variables u_ij
    
    
    
    IloRangeArray constraint_permutation_rows; //Constraint for the permutation matrix rows
    IloRangeArray constraint_permutation_cols; //Constraint for the permutation matrix columns
   
    
    //Objective function
    
    IloObjective obj_function;     //Define the objective function described in the paper
    
    //Cplex environment
    
    IloCplex cplex;
    
    //Results
    //NumArray2 results_u_ij;                 
    //NumArray2 results_x_ij;  
    //IloNum results_obj;   
    

public:

	Exo2(Graph U, Graph V);
	~Exo2();


	//Functions to define variables
    void define_x_ij();
    void define_u_ij();
    
    //Function to define constraints
    void define_constraints_absolute1();
    void define_constraints_absolute2();
    void define_constraint_permutation_rows();
    void define_constraint_permutation_cols();
    
    //Function to define the objective function
    void define_objective_function();
    
    //Function to build the model by calling all functions 
    void build_model();
    
    //Function to solve the model by calling function solve from cplex and display the status of the solution
    void solve_model();
};
