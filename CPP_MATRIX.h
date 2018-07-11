// Program: CPP_MATRIX.h
// Programmer: Michael Richards
// Date: 2/3/16

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

typedef int* u_int_ptr;

class CPP_MATRIX
{
	public:
		
	CPP_MATRIX();
	CPP_MATRIX(CPP_MATRIX&); // copy constructor
	CPP_MATRIX(int, int);	 // constructor with established dimensions
	~CPP_MATRIX();			 // destructor
	
	/*****************************************************************************/
	/*****************************************************************************/
	
	// Entry Manipulation
	unsigned get_column_index(int);
	unsigned get_row_index(int);
	void set_matrix_entry(int, int, int);
	int get_matrix_entry(int, int);
	void increment_matrix_entry(int, int, int);
	
	/*****************************************************************************/
	/*****************************************************************************/
	
	int get_rows();
	int get_columns();
	int get_determinant();
	
	/*****************************************************************************/
	/*****************************************************************************/
		
	// File Manipulation
	bool file_input_matrix(int, int, string);
	void file_output_matrix(int,int, string);
	
	/*****************************************************************************/
	/*****************************************************************************/
	
	// Matrix Output Functions
	void output_matrix();
	void setw_output_matrix(int);
	void output_row(int);
	void output_column(int);
	void output_diagonal();
	
	/*****************************************************************************/
	/*****************************************************************************/
	
	// Friend Functions (Matrix Functions)
	
	friend CPP_MATRIX row_sum_vector(CPP_MATRIX& this_matrix);
	friend CPP_MATRIX column_sum_vector(CPP_MATRIX& this_matrix);
	
	friend CPP_MATRIX get_row(CPP_MATRIX&, int);
	friend CPP_MATRIX get_column(CPP_MATRIX&, int);
	friend CPP_MATRIX get_diagonal(CPP_MATRIX&);
	
	friend int diagonal_sum(CPP_MATRIX& this_matrix);
	friend void row_swap(CPP_MATRIX& this_matrix, int left, int right);
	friend void column_swap(CPP_MATRIX& this_matrix, int left, int right);
	
	// Shift functions
	friend void column_shift_up(CPP_MATRIX&, int);
	friend void column_shift_down(CPP_MATRIX&, int);
	friend void row_shift_left(CPP_MATRIX&, int);
	friend void row_shift_right(CPP_MATRIX&, int);
	friend void diagonal_shift_down_right(CPP_MATRIX&);
	friend void diagonal_shift_up_left(CPP_MATRIX&);
	
	// Matrix Math functions
	
	// Multiplication
	friend void multiply_row(CPP_MATRIX&,int,int);
	friend void multiply_column(CPP_MATRIX&,int,int);
	
	// Division
	friend void divide_row(CPP_MATRIX&,int,int);
	friend void divide_column(CPP_MATRIX&,int,int);
	
	// Addition
	friend void add_rows(CPP_MATRIX&,int,int);
	friend void add_columns(CPP_MATRIX&,int,int);
	
	// Subtraction
	friend void subtract_rows(CPP_MATRIX&,int,int);
	friend void subtract_columns(CPP_MATRIX&,int,int);
	
	friend CPP_MATRIX transpose(CPP_MATRIX&);
	
	// Overloaded Operators	
	friend CPP_MATRIX operator *(CPP_MATRIX&, CPP_MATRIX&);
	friend CPP_MATRIX operator +(CPP_MATRIX&, CPP_MATRIX&);
	friend CPP_MATRIX operator -(CPP_MATRIX&, CPP_MATRIX&);
	//CPP_MATRIX operator =(CPP_MATRIX);
		
	private:
		
	double det(int, double[][10]);
		
	u_int_ptr* alt_matrix;
	int rows;
	int columns;	
};

/*****************************************************************************/
/*****************************************************************************/

CPP_MATRIX::CPP_MATRIX()
{
	alt_matrix = new int*[10];
	
	for(unsigned i = 0; i < 10; i++)
	{
		alt_matrix[i] = new int[10];
	}
	rows = 10;
	columns = 10;
	
	for(unsigned i = 0; i < 10; i++)
	{
		alt_matrix[i] = new int[10];
		for(unsigned j = 0; j < 10; j++)
		{
			alt_matrix[i][j] = 0;
		}
	}
}

/*****************************************************************************/

CPP_MATRIX::CPP_MATRIX(CPP_MATRIX& this_matrix)
{
	CPP_MATRIX copy_matrix(this_matrix.get_rows(), this_matrix.get_columns());
	
	for(int i = 0; i < this_matrix.get_rows(); i++)
	{
		for(int j = 0; j < this_matrix.get_columns(); j++)
		{
			copy_matrix.set_matrix_entry(i,j, this_matrix.get_matrix_entry(i,j));
		}
	}
}

/*****************************************************************************/

CPP_MATRIX::CPP_MATRIX(int left, int right)
{
	alt_matrix = new int*[left];
	rows = left;
	columns = right;
	
	for(unsigned i = 0; i < left; i++)
	{
		alt_matrix[i] = new int[right];
		for(unsigned j = 0; j < right; j++)
		{
			alt_matrix[i][j] = 0;
		}
	}	
}

/*****************************************************************************/

CPP_MATRIX::~CPP_MATRIX()
{
	for(unsigned i = 0; i < rows; i++)
	{
		delete[] alt_matrix[i];
	}
	
	delete[] alt_matrix;
	
	rows = 0;
	columns = 0;
}

/*****************************************************************************/

unsigned CPP_MATRIX::get_column_index(int entry)
{
	unsigned counter = 0;
	
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < columns; j++)
		{
			if(alt_matrix[i][j] == entry)
			{
				return j;
				break;
			}
			else
			{
				counter++;
			}
		}
	}
	
	if(counter == (rows * columns))
	{
		return 0;
	}
}

/*****************************************************************************/

unsigned CPP_MATRIX::get_row_index(int entry)
{
	unsigned counter = 0;
	
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < columns; j++)
		{
			if(alt_matrix[i][j] == entry)
			{
				return i;
				break;
			}
			else
			{
				counter++;
			}
		}
	}
	
	if(counter == (rows * columns))
	{
		return 0;
	}
}

/*****************************************************************************/

void CPP_MATRIX::set_matrix_entry(int left, int right, int entry)
{
	if((left <= rows) || (right <= columns))
	{
		alt_matrix[left][right] = entry;
	}
}

/*****************************************************************************/

int CPP_MATRIX::get_matrix_entry(int left, int right)
{
	if((left <= rows) || (right <= columns))
	{
		return alt_matrix[left][right];
	}
}

/*****************************************************************************/

void CPP_MATRIX::increment_matrix_entry(int row_index, int column_index, int adding_constant)
{
		if((row_index >= rows) || (column_index >= rows))
		{
			cout << "FAILURE: Row or Column index out of range... \n\n";
		}
		else
		{
			alt_matrix[row_index][column_index] += adding_constant;
		}
}

/*****************************************************************************/
int CPP_MATRIX::get_rows()
{
	return rows;
}

/*****************************************************************************/

int CPP_MATRIX::get_columns()
{
	return columns;
}

/*****************************************************************************/

bool CPP_MATRIX::file_input_matrix(int number_of_rows, int number_of_columns, string filename)
{
	char* char_file;
	
	char_file = new char[filename.length() + 1];
	
	for(int i = 0; i < filename.length(); i++)
	{
		char_file[i] = filename[i];
	}
	
	char_file[filename.length()] = '\0';
	
	ifstream file_stream;
	
	int stream_entry = 0;
	bool eof_signal = false;
	bool out_of_bounds = false;
	
	file_stream.open(char_file);
	
	if(!file_stream)
	{
		cout << "FAILURE: File cannot be found...\n\n";
		eof_signal = true;
		return false;
	}
	
	if((number_of_rows > rows) || (number_of_columns > columns))
	{
		out_of_bounds = true;
		return false;
	}
	
	if(out_of_bounds == true)
	{
		cout << "FAILURE: Index out of bounds... \n\n";
		file_stream.close();
		return false;
	}	
	else if(eof_signal != true)
	{
		for(int i = 0; i < number_of_rows; i++)
		{
			for(int j = 0; j < number_of_columns; j++)
			{				
					file_stream >> stream_entry;
					
					if(!file_stream)
					{
						eof_signal = true;
						return false;
						break;
					}
					else
					{	
						alt_matrix[i][j] = stream_entry;
					}
			}
		
			if(eof_signal == true)
			{
				cout << "FAILURE: End-of-file met within the file... \n\n";
				break;
			}
		}
	
		file_stream.close();
		
		return true;
	}
	else
	{
		file_stream.close();
	}
}

/*****************************************************************************/

void CPP_MATRIX::file_output_matrix(int number_of_rows, int number_of_columns, string filename)
{
	ofstream file_stream;
	
	char* char_file;
	
	char_file = new char[filename.length() + 1];
	
	for(int i = 0; i < filename.length(); i++)
	{
		char_file[i] = filename[i];
	}
	
	char_file[filename.length()] = '\0';
	
	file_stream.open(char_file);
	
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < rows; j++)
		{
			file_stream << alt_matrix[i][j] << " "; 
		}
		file_stream << "\n";
	}
	
	file_stream.close();
}

/*****************************************************************************/

void CPP_MATRIX::output_matrix()
{
	for(unsigned line_1 = 0; line_1 < (rows * 8) + 5; line_1++)
	{
		std::cout << "-";
	}
	std::cout << "\n";
		
	for(unsigned i = 0; i < rows; i++)
	{		
		for(unsigned j = 0; j < columns; j++)
		{
			std::cout << setw(12) << alt_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
		
	for(unsigned line_1 = 0; line_1 < (rows * 8) + 5; line_1++)
	{
		std::cout << "-";
	}
	std::cout << "\n\n";
}

/*****************************************************************************/

void CPP_MATRIX::setw_output_matrix(int width_constant)
{
	for(unsigned line_1 = 0; line_1 < (rows * 8) + 5; line_1++)
	{
		std::cout << "-";
	}
	std::cout << "\n";
		
	for(unsigned i = 0; i < rows; i++)
	{		
		for(unsigned j = 0; j < columns; j++)
		{
			std::cout << setw(width_constant) << alt_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
		
	for(unsigned line_1 = 0; line_1 < (rows * 8) + 5; line_1++)
	{
		std::cout << "-";
	}
	std::cout << "\n\n";
}

/*****************************************************************************/

void CPP_MATRIX::output_diagonal()
{
	for(int i = 0; i < rows; i++)
	{
		cout << alt_matrix[i][i] << " ";
	}
	cout << "\n\n";
}

/*****************************************************************************/

CPP_MATRIX operator +(CPP_MATRIX& matrix1, CPP_MATRIX& matrix2)
{
	CPP_MATRIX temp(matrix1.get_rows(), matrix1.get_columns());
	
	if((matrix1.get_rows() == matrix2.get_rows()) && (matrix1.get_columns() == matrix2.get_columns()))
	{		
		for(int i = 0; i < matrix1.get_rows(); i++)
		{
			for(int j = 0; j < matrix1.get_columns(); j++)
			{
				temp.set_matrix_entry(i,j, matrix1.get_matrix_entry(i,j) + matrix2.get_matrix_entry(i,j));
			}
		}	
	}
	
	return temp;
}

/*****************************************************************************/

CPP_MATRIX operator -(CPP_MATRIX& matrix1, CPP_MATRIX& matrix2)
{
	CPP_MATRIX temp(matrix1.get_rows(), matrix1.get_columns());
	
	if((matrix1.get_rows() == matrix2.get_rows()) && (matrix1.get_columns() == matrix2.get_columns()))
	{		
		for(int i = 0; i < matrix1.get_rows(); i++)
		{
			for(int j = 0; j < matrix1.get_columns(); j++)
			{
				temp.set_matrix_entry(i,j, matrix1.get_matrix_entry(i,j) - matrix2.get_matrix_entry(i,j));
			}
		}	
	}
	
	return temp;
}

/*****************************************************************************/

CPP_MATRIX operator *(CPP_MATRIX& matrix1, CPP_MATRIX& matrix2)
{	
	int a[10][10], b[10][10], mult[10][10], r1, c1, r2, c2, i, j, k;
	
	r1 = matrix1.get_rows();
	r2 = matrix2.get_rows();
	c1 = matrix1.get_columns();
	c2 = matrix2.get_columns();
	
	CPP_MATRIX new_mult(r1,c2);
	
	 for(i = 0; i < r1; ++i)
        for(j = 0; j < c1; ++j)
        {
            a[i][j]	= matrix1.get_matrix_entry(i,j);       
        }
        
     for(i = 0; i < r2; ++i)
        for(j = 0; j < c2; ++j)
        {
            b[i][j] = matrix2.get_matrix_entry(i,j);
        }
	
	if(c1 == r2)
	{
		// Multiplying matrix a and b and storing in array mult.
		
    	for(i = 0; i < r1; ++i)
        	for(j = 0; j < c2; ++j)
            	for(k = 0; k < c1; ++k)
            	{
        	        mult[i][j] += a[i][k] * b[k][j];
    	            new_mult.set_matrix_entry(i,j,mult[i][j]);
   	         	}
    }
      
    return new_mult;
}

/*
CPP_MATRIX CPP_MATRIX::operator =(CPP_MATRIX this_matrix)
{
	CPP_MATRIX temp(this_matrix.get_rows(), this_matrix.get_columns());
	
	temp.alt_matrix = new int*[this_matrix.get_rows()];
	
	for(int i = 0; i < this_matrix.get_rows(); i++)
	{
		temp.alt_matrix[i] = new int[this_matrix.get_columns()];
	}
	
	for(int i = 0; i < this_matrix.get_rows(); i++)
	{
		for(int j = 0; j < this_matrix.get_columns(); j++)
		{
			temp.set_matrix_entry(i,j, this_matrix.get_matrix_entry(i,j));
		}
	}
	
	return temp;
}

*/

