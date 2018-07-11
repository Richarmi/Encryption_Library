// Program: CPP_MATRIX_FUNCTIONS.h
// Programmer: Michael Richards
// Date: 2/3/16

#include "CPP_MATRIX.h"

/*****************************************************************************/
/*****************************************************************************/

void column_swap(CPP_MATRIX& this_matrix, int left, int right)
{
	for(unsigned i = 0; i < this_matrix.rows; i++)
	{
		int temp = this_matrix.alt_matrix[i][left];
		this_matrix.alt_matrix[i][left] = this_matrix.alt_matrix[i][right];
		this_matrix.alt_matrix[i][right] = temp;
	}
}

/*****************************************************************************/

void row_swap(CPP_MATRIX& this_matrix, int left, int right)
{
	for(unsigned i = 0; i < this_matrix.get_columns(); i++)
	{
		unsigned temp = this_matrix.alt_matrix[left][i];
		this_matrix.alt_matrix[left][i] = this_matrix.alt_matrix[right][i];
		this_matrix.alt_matrix[right][i] = temp;
	}
}

/*****************************************************************************/

CPP_MATRIX row_sum_vector(CPP_MATRIX& this_matrix)
{
	CPP_MATRIX row_sum(this_matrix.rows, 1);
	
	for(unsigned i = 0; i < this_matrix.rows; i++)
	{
		unsigned accumulator = 0;
			
		for(unsigned j = 0; j < this_matrix.columns; j++)
		{
			accumulator += this_matrix.alt_matrix[i][j];
		}
		
		row_sum.alt_matrix[i][0] = accumulator;
	}
	
	return row_sum;
}

/*****************************************************************************/

CPP_MATRIX column_sum_vector(CPP_MATRIX& this_matrix)
{
	CPP_MATRIX column_sum(1, this_matrix.columns);	
	
	for(unsigned i = 0; i < this_matrix.columns; i++)
	{
		int accumulator = 0;
		
		for(unsigned j = 0; j < this_matrix.rows; j++)
		{
			accumulator += this_matrix.alt_matrix[i][j];
		}
		
		column_sum.alt_matrix[0][i] = accumulator;
	}
	
	return column_sum;
}

/*****************************************************************************/

CPP_MATRIX get_row(CPP_MATRIX& this_matrix, int row_index)
{
	CPP_MATRIX row_vector(1,this_matrix.columns);
	
	for(unsigned i = 0; i < this_matrix.columns; i++)
	{
		row_vector.alt_matrix[0][i] = this_matrix.alt_matrix[row_index][i];
	}
	
	return row_vector;
}

/*****************************************************************************/

CPP_MATRIX get_column(CPP_MATRIX& this_matrix, int column_index)
{
	CPP_MATRIX column_vector(this_matrix.rows,1);
	
	for(unsigned i = 0; i < this_matrix.rows; i++)
	{
		column_vector.alt_matrix[i][0] = this_matrix.alt_matrix[i][column_index];
	}
	
	return column_vector;
}

/*****************************************************************************/

CPP_MATRIX get_diagonal(CPP_MATRIX& this_matrix)
{
	CPP_MATRIX diagonal(this_matrix.rows,this_matrix.columns);
	
	for(unsigned i = 0; i < this_matrix.rows; i++)
	{
		for(unsigned j = 0; j < this_matrix.columns; j++)
		{
			diagonal.alt_matrix[i][j] = 0;
		}
	}
	
	for(unsigned i = 0; i < this_matrix.columns; i++)
	{
		diagonal.alt_matrix[i][i] = this_matrix.alt_matrix[i][i];
	}
	
	return diagonal;
}

/*****************************************************************************/

int diagonal_sum(CPP_MATRIX& this_matrix)
{
	int accumulator = 0;
	
	if(this_matrix.rows == this_matrix.columns)
	{
		for(unsigned i = 0; i < this_matrix.rows; i++)
		{
			accumulator += this_matrix.alt_matrix[i][i];
		}
		
		return accumulator;
	}
	else
	{
		accumulator = 0;
		return accumulator;
	}
}

/*****************************************************************************/

void column_shift_down(CPP_MATRIX& this_matrix, int column_index)
{
	for(unsigned i = this_matrix.rows - 1; i > 0 ; i--)
	{
		int temp = this_matrix.alt_matrix[i][column_index];
		this_matrix.alt_matrix[i][column_index] = this_matrix.alt_matrix[i-1][column_index];
		this_matrix.alt_matrix[i-1][column_index] = temp;
	}
}

/*****************************************************************************/

void column_shift_up(CPP_MATRIX& this_matrix, int column_index)
{
	for(unsigned i = 0; i < this_matrix.rows - 1; i++)
	{
		int temp = this_matrix.alt_matrix[i][column_index];
		this_matrix.alt_matrix[i][column_index] = this_matrix.alt_matrix[i+1][column_index];
		this_matrix.alt_matrix[i+1][column_index] = temp;
	}
}

/*****************************************************************************/

void row_shift_left(CPP_MATRIX& this_matrix, int row_index)
{
	for(unsigned i = 0; i < this_matrix.columns - 1; i++)
	{	
		unsigned temp = this_matrix.alt_matrix[row_index][i];
		this_matrix.alt_matrix[row_index][i] = this_matrix.alt_matrix[row_index][i+1];
		this_matrix.alt_matrix[row_index][i+1] = temp;
	}
}

/*****************************************************************************/

void row_shift_right(CPP_MATRIX& this_matrix, int row_index)
{
	for(unsigned i = this_matrix.columns - 1; i > 0 ; i--)
	{		
		int temp = this_matrix.alt_matrix[row_index][i];
		this_matrix.alt_matrix[row_index][i] = this_matrix.alt_matrix[row_index][i-1];
		this_matrix.alt_matrix[row_index][i-1] = temp;
	}
}

/*****************************************************************************/

void diagonal_shift_down_right(CPP_MATRIX& this_matrix)
{
	if(this_matrix.columns == this_matrix.rows)
	{
		for(unsigned i = this_matrix.columns - 1; i > 0; i--)
		{
			int temp = this_matrix.alt_matrix[i][i];
			this_matrix.alt_matrix[i][i] = this_matrix.alt_matrix[i-1][i-1];
			this_matrix.alt_matrix[i-1][i-1] = temp;
		}
	}
}

/*****************************************************************************/

void diagonal_shift_up_left(CPP_MATRIX& this_matrix)
{
	if(this_matrix.columns == this_matrix.rows)
	{
		for(unsigned i = 0; i < this_matrix.columns - 1; i++)
		{
			int temp = this_matrix.alt_matrix[i][i];
			this_matrix.alt_matrix[i][i] = this_matrix.alt_matrix[i+1][i+1];
			this_matrix.alt_matrix[i+1][i+1] = temp;
		}
	}
}

/*****************************************************************************/

void multiply_row(CPP_MATRIX& this_matrix, int current_row, int constant)
{
	for(unsigned i = 0; i < this_matrix.columns; i++)
	{
		this_matrix.alt_matrix[current_row][i] *= constant;
	}
}

/*****************************************************************************/

void divide_row(CPP_MATRIX& this_matrix, int current_row, int constant)
{
	for(unsigned i = 0; i < this_matrix.columns; i++)
	{
		this_matrix.alt_matrix[current_row][i] /= constant;
	}
}

/*****************************************************************************/

void multiply_column(CPP_MATRIX& this_matrix, int current_column, int constant)
{
	for(unsigned i = 0; i < this_matrix.rows; i++)
	{
		this_matrix.alt_matrix[i][current_column] *= constant;
	}
}

/*****************************************************************************/

void divide_column(CPP_MATRIX& this_matrix, int current_column, int constant)
{
	for(int i = 0; i < this_matrix.rows; i++)
	{
		this_matrix.alt_matrix[i][current_column] /= constant;
	}
}

/*****************************************************************************/

void add_rows(CPP_MATRIX& this_matrix, int left, int right)
{
	for(int i = 0; i < this_matrix.columns; i++)
	{
		this_matrix.alt_matrix[left][i] += this_matrix.alt_matrix[right][i];
	}
}

/*****************************************************************************/

void add_columns(CPP_MATRIX& this_matrix, int left, int right)
{
	for(int i = 0; i < this_matrix.columns; i++)
	{
		this_matrix.alt_matrix[i][left] += this_matrix.alt_matrix[i][right];
	}
}

/*****************************************************************************/

void subtract_rows(CPP_MATRIX& this_matrix, int left, int right)
{
	for(int i = 0; i < this_matrix.columns; i++)
	{
		this_matrix.alt_matrix[left][i] -= this_matrix.alt_matrix[left][i];
	}
}

/*****************************************************************************/

void subtract_columns(CPP_MATRIX& this_matrix, int left, int right)
{
	for(int i = 0; i < this_matrix.columns; i++)
	{
		this_matrix.alt_matrix[i][left] -= this_matrix.alt_matrix[i][left];
	}
}

/*****************************************************************************/

// based on the program from http://www.programmingsimplified.com/c-program-transpose-matrix
CPP_MATRIX transpose(CPP_MATRIX& this_matrix)
{
	CPP_MATRIX trans(this_matrix.get_columns(), this_matrix.get_rows());
	int a[10][10], r, c, i, j;
	
	r = this_matrix.get_rows();
	c = this_matrix.get_columns();
    
     // Storing element of matrix entered by user in array a[][].
    for(i = 0; i < r; ++i)
    	for(j = 0; j < c; ++j)
    	{
       		a[i][j] = this_matrix.get_matrix_entry(i,j);
    	}

    // Finding transpose of matrix a[][] and storing it in array trans[][].
    for(i = 0; i < r; ++i)
        for(j = 0; j < c; ++j)
        {
            trans.set_matrix_entry(j,i, a[i][j]);
        }
        
    return trans;    
}

/*****************************************************************************/

int CPP_MATRIX::get_determinant()
{
	double matrix_copy[10][10];
	double determinant = 0;
	int int_determinant = 0;
	
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			matrix_copy[i][j] = static_cast<double>(alt_matrix[i][j]);
		}
	}
	
	if(rows == columns)
	{
		determinant = det(rows, matrix_copy);
		int_determinant = static_cast<int>(determinant);
	}
	
	return int_determinant;
}

/*****************************************************************************/

double CPP_MATRIX::det(int n, double mat[10][10])
{
    double d = 0;
    int c, subi, i, j, subj;
    double submat[10][10];  

    if (n == 2) 
    {
        return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
    }
    else
    {  
        for(c = 0; c < n; c++)
        {  
            subi = 0;  

            for(i = 1; i < n; i++)
            {  
                subj = 0;

                for(j = 0; j < n; j++)
                {    
                    if (j == c)
                    {
                        continue;
                    }

                    submat[subi][subj] = mat[i][j];
                    subj++;
                }

                subi++;
            }

	        d = d + (pow(-1 ,c) * mat[0][c] * det(n - 1 ,submat));
        }
    }

    return d;
}

/*****************************************************************************/
/*****************************************************************************/	
