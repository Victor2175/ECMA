#include "stdafx.h"
#include "Matrix.h"

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
Matrix::Matrix(int n, FILE * m_log)
{
    m_size = n;
    m_matrix = new int*[n];
	m_edges = 0;
    for(int i = 0;i < n;++i) m_matrix[i] = new int[n];
}

///////////////////////////////////////////////////////////////////////////////
// Addition
///////////////////////////////////////////////////////////////////////////////
Matrix * Matrix::add(Matrix * m)
{
    Matrix * res = new Matrix(m_size);

    for(int i = 0;i < m_size;++i)
        for(int j = 0;j < m_size;++j)
        {
            int r = get(i,j) + m->get(i,j);
            res->set(i,j,r);
        }

    return res;
}

///////////////////////////////////////////////////////////////////////////////
// subtraction
///////////////////////////////////////////////////////////////////////////////
Matrix * Matrix::subtract(Matrix * m)
{
    Matrix * res = new Matrix(m_size);

    for(int i = 0;i < m_size;++i)
        for(int j = 0;j < m_size;++j)
        {
            int r = get(i,j) - m->get(i,j);
            res->set(i,j,r);
        }

    return res;
}

///////////////////////////////////////////////////////////////////////////////
// Multiplication
///////////////////////////////////////////////////////////////////////////////
Matrix * Matrix::multiply(Matrix * m)
{
    Matrix * res = new Matrix(m_size);

    for(int i = 0;i < m_size;++i)
        for(int j = 0;j < m_size;++j)
        {
            int r = 0;
            for(int k = 0;k < m_size;++k) r += get(i,k) * m->get(k,j);
            res->set(i,j,r);
        }

    return res;
}

///////////////////////////////////////////////////////////////////////////////
// Inverse
///////////////////////////////////////////////////////////////////////////////
Matrix * Matrix::transpose()
{
    Matrix * res = new Matrix(m_size);

	for(int i = 0;i < m_size;++i)
	{
        for(int j = i;j < m_size;++j)
        {
			int value_ij = get(i,j);
			int value_ji = get(j,i);
			res->set(i,j, value_ji);
			res->set(j,i, value_ij);
        }
	}

	return res;
}

///////////////////////////////////////////////////////////////////////////////
// Read matrix from file
///////////////////////////////////////////////////////////////////////////////
bool Matrix::read(char * file_name)
{
    bool b = true;
    FILE * in = fopen(file_name, "r");

    if(in == NULL)
    {
        b = false;
    }
    else
    {
        for(int i = 0;i < m_size && b;++i)
            for(int j = 0;j < m_size;++j)
            {
                int value;
                b = (fscanf(in, "%lf", &value) == 1);
                if(b)
                {
                    set(i,j,value);
                }
                else
                {
                    break;
                }
            }
    }

    return b;

}

///////////////////////////////////////////////////////////////////////////////
// Display Matrix contents
///////////////////////////////////////////////////////////////////////////////
void Matrix::display(char * matrix_name)
{
    printf ("the matrix %s is:\n", matrix_name);
    for(int i = 0;i < m_size;++i)
    {
        for(int j = 0;j < m_size;++j)
        {

            int value = get(i,j);
			printf("%d", value);
            if(j != m_size - 1) printf(" ");
        }

        printf("\n");
    }
    
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////
Matrix::~Matrix()
{
    for(int i = 0;i < m_size;++i) delete [] m_matrix[i];
    m_size = 0;
    delete [] m_matrix;
}

void Matrix::equalize(Matrix * m)
{
	for(int i=0; i<m_size; i++)
	{
		for(int j=0; j< m_size ; j++)
		{
			m_matrix[i][j] = m->get(i,j);
		}
	}
}


void Matrix::read_from_vector(vector< vector<int> > adj_matrix)
{
	int count =0;
	for(int i = 0; i < m_size; i++)
	{
		for(int j=i; j < m_size ; j++)
		{
			count += adj_matrix[i][j];
			set(i,j, adj_matrix[i][j]);
			set(j,i, adj_matrix[i][j]);
		}

	}
	m_edges = count;

}

void Matrix::Switch_Node(int index1, int index2)
{
	for(int i = 0; i < m_size; i++)
	{
		int value1i = get(index1, i);
		int value2i = get(index2, i);
		set(index1,i, value2i);
		set(i, index1, value2i);
		set(index2, i, value1i);
		set(i, index2, value1i);
	}

}


void Matrix::Random_switch()
{
	int node_index1 = rand()%(m_size);
	int node_index2 = rand()%(m_size);
	while(node_index2 == node_index1)
	{
		node_index2  = rand()%(m_size);
	}

	Switch_Node(node_index1, node_index2);
}

	

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
