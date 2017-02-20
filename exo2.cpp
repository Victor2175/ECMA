#include "stdafx.h"
#include "exo2.h"
#include <vector>

using namespace std;

Exo2::Exo2(Graph U, Graph V){

	
	G = U;
	Gbar = V;


	//Define concert environment;
    
	model = IloModel(env);
    
	cplex = IloCplex(env);


	//creation de deux matrices d'adj de de même taillle
	Nmax = max(G.getNbNode(), Gbar.getNbNode());
	vector<int> v;
	for (int i = 0; i<Nmax; i++){
		a_ij.push_back(v);
		abar_ij.push_back(v);
		for (int j = 0; j<Nmax; j++){
			a_ij[i].push_back(0);
			abar_ij[i].push_back(0);
		}
	}



	//initialisation des matrices d'adjacences
	for (int i = 0; i<G.getNbNode(); i++){
		for (int j = 0; j<G.getNbNode(); j++){
			a_ij[i][j]=G.getAdjMatrix()[i][j];
		}
	}
	for (int i = 0; i<Gbar.getNbNode(); i++){
		for (int j = 0; j<Gbar.getNbNode(); j++){
			abar_ij[i][j]=Gbar.getAdjMatrix()[i][j];
		}
	}
}

Exo2::~Exo2(){

	env.end();
}


//Define the variables
void Exo2::define_x_ij(){
    char var_name[30];
    
	x_ij = NumVarArray2(env);
	for(int i = 0; i< Nmax ; i ++)
	{
		x_ij.add(IloNumVarArray(env, Nmax));
		for(int j = 0; j< Nmax ; j ++)
		{
			x_ij[i][j] = IloNumVar(env, 0.0, 1.0,ILOINT);
			sprintf_s(var_name, "x_%d%d",i,j);
			x_ij[i][j].setName(var_name);
		}
	}
  
}

void Exo2::define_u_ij(){
    char var_name[30];
    
	u_ij = NumVarArray2 (env);
	for(int i = 0; i< Nmax ; i ++)
	{
		
		u_ij.add(IloNumVarArray(env, Nmax));
		for(int j = 0; j< Nmax ; j ++)
		{
			u_ij[i][j] = IloNumVar(env, 0.0, IloInfinity,ILOFLOAT);
			sprintf_s(var_name, "u_%d%d",i,j);
			u_ij[i][j].setName(var_name);
		}
	}
  
}

void Exo2::define_constraints_absolute1(){
	char con_name[30];

	RangeArray2 constraints_absolute1(env); 
    for (int i = 0 ; i < Nmax ; i++) 
	{
		constraints_absolute1.add(IloRangeArray(env, Nmax));

		for(int j = 0; j < Nmax; j++)
		{
			constraints_absolute1[i][j] = IloRange(env, 0.0, IloInfinity);
			sprintf_s(con_name, "constraint_absolute1_%d%d", i, j);
			constraints_absolute1[i][j].setName(con_name);
			
			IloExpr expression(env);
			expression += u_ij[i][j];

			for(int k =0; k < Nmax ; k++)
			{
				expression -= (abar_ij[i][k] * x_ij[k][j] - x_ij[i][k] * a_ij[k][j]);
			}

	
			constraints_absolute1[i][j].setExpr(expression);
			expression.end();

			//Add the constraint i,j to the model
			model.add(constraints_absolute1[i][j]);
		}
    }
	
}

void Exo2::define_constraints_absolute2(){
	
	char con_name[30];

	RangeArray2 constraints_absolute2(env); 
    for (int i = 0 ; i < Nmax ; i++) 
	{
		constraints_absolute2.add(IloRangeArray(env, Nmax));

		for(int j = 0; j < Nmax; j++)
		{
			constraints_absolute2[i][j] = IloRange(env, 0.0, IloInfinity);
			sprintf(con_name, "constraint_absolute2_%d%d", i, j);
			constraints_absolute2[i][j].setName(con_name);
			
			IloExpr expression(env);
			expression += u_ij[i][j];

			for(int k =0; k < Nmax ; k++)
			{
				expression -= (a_ij[k][j] * x_ij[i][k] - x_ij[k][j] * abar_ij[i][k]);
			}
			constraints_absolute2[i][j].setExpr(expression);
			expression.end();

			//Add the constraint i,j to the model
			model.add(constraints_absolute2[i][j]);
		}
    }
    
}

void Exo2::define_constraint_permutation_rows(){
	
	char con_name[30];

	constraint_permutation_rows = IloRangeArray(env, Nmax);

	for(int i = 0; i < Nmax; i++)
	{
		constraint_permutation_rows[i] = IloRange(env, 0.0, 0.0);
		sprintf(con_name, "constraint_permutation_rows_%d", i);
		constraint_permutation_rows[i].setName(con_name);

		IloExpr expression(env);

		for(int j =0; j < Nmax ; j++)
		{
			expression += x_ij[i][j];
		}
		expression -= 1;
		constraint_permutation_rows[i].setExpr(expression);
		expression.end();

		model.add(constraint_permutation_rows[i]);
	}
}
    
void Exo2::define_constraint_permutation_cols(){
	
	char con_name[30];

	constraint_permutation_cols = IloRangeArray(env, Nmax);

	for(int i = 0; i < Nmax; i++)
	{
		constraint_permutation_cols[i] = IloRange(env, 0.0, 0.0);
		sprintf(con_name, "constraint_permutation_cols_%d", i);
		constraint_permutation_cols[i].setName(con_name);

		IloExpr expression(env);

		for(int j =0; j < Nmax ; j++)
		{
			expression += x_ij[j][i];
		}
		expression -= 1;
		constraint_permutation_cols[i].setExpr(expression);
		expression.end();

		model.add(constraint_permutation_cols[i]);
	}
}
    

void Exo2::define_objective_function(){

	obj_function  = IloMinimize(env);
    IloExpr expression(env);

	for (int i = 0 ; i < Nmax ; i++) {
		for(int j = 0; j < Nmax ; j++) {
			expression += u_ij[i][j];
		}
    } 
    obj_function.setExpr(expression);
    model.add(obj_function);
    
    expression.end();
}

//Function to build the model by calling all functions 
void Exo2::build_model(){

	//if(G.getNbNode() == Gbar.getNbNode())
	//{
		define_x_ij();
		define_u_ij();

        
		define_constraints_absolute1();
		define_constraints_absolute2();

	
		define_constraint_permutation_rows();
		define_constraint_permutation_cols();

    
		define_objective_function();

		cout << "model built with success" << endl;
	//}
	//else
	//{
		//cout << "The model can't be created since the graphs don't have the same size" << endl;
	//}

}

void Exo2::solve_model(){

    int obj = abs(G.getNbEdges() - Gbar.getNbEdges());
	//if(G.getNbNode() == Gbar.getNbNode())
	//{
		
		cplex.extract(model);
		cplex.solve();
		cout << "The solution obtained is "  << cplex.getCplexStatus() << endl;
		cout << "The value of the objective function is " << cplex.getObjValue() << endl;
		cout << "Value to reach is " << obj << endl;

		if(cplex.getObjValue() == obj)
		{
			cout << "The graphs G and Gbar are isomorph !" << endl;
		}
		else
		{
			cout << "The graphs G and Gbar are not isomorph !" << endl;
		}
	//}
	//else
	//{
		//cout << "The model can't  be solved ! The graphs don't have the same size" << endl;
	//}
}