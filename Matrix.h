#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Matrix
{
    int m_size;
    int ** m_matrix;
    FILE * m_log;
    int m_edges;

    public :
        Matrix(int n, FILE * m_log = stderr);
		void equalize(Matrix * m);
		int get_size(){return m_size; };
		int get_edges(){return m_edges; };
		int get(int i, int j){return m_matrix[i][j]; };
		void set(int i, int j, int value){ m_matrix[i][j] = value; };
        Matrix* add(Matrix *  m);
        Matrix* subtract(Matrix * m);
        Matrix* multiply(Matrix * m);
        Matrix* transpose();
		void Switch_Node(int index1, int index2);
		void Random_switch();
		void read_from_vector(vector< vector<int> > adj_matrix);
        bool read(char * file_name);
        void display(char * matrix_name);
        ~Matrix();
};





/*
int main(int argc, char ** argv)
{
    Matrix m1(2), m2(2);
    
    m1.read("m1.m");
    m2.read("m2.m");
    Matrix * sum  = m1.add(&m2);
    Matrix * diff = m1.subtract(&m2);
    Matrix * mul  = m1.multiply(&m2);
    sum->display("sum");
    diff->display("difference");
    mul->display("multiplication");

    return 0;
}*/


#endif
