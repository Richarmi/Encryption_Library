// Program: Playfair.cpp
// Programmer: Michael Richards
// Date: 8/4/16

#include <iostream>
#include <string>
#include "Encryption.h"
//#include "CPP_MATRIX_FUNCTIONS.h"

using namespace std;

/*****************************************************************************/

int main()
{
	char playfair_matrix[5][5];
	
	playfair_matrix[0][0] = 'p'; playfair_matrix[0][1] = 'l'; playfair_matrix[0][2] = 'a';
	playfair_matrix[0][3] = 'y'; playfair_matrix[0][4] = 'f';
	
	playfair_matrix[1][0] = 'i'; playfair_matrix[1][1] = 'r'; playfair_matrix[1][2] = 'b';
	playfair_matrix[1][3] = 'c'; playfair_matrix[1][4] = 'd';
	
	playfair_matrix[2][0] = 'e'; playfair_matrix[2][1] = 'g'; playfair_matrix[2][2] = 'h';
	playfair_matrix[2][3] = 'k'; playfair_matrix[2][4] = 'm';
	
	playfair_matrix[3][0] = 'n'; playfair_matrix[3][1] = 'o'; playfair_matrix[3][2] = 'q';
	playfair_matrix[3][3] = 's'; playfair_matrix[3][4] = 't';
	
	playfair_matrix[4][0] = 'u'; playfair_matrix[4][1] = 'v'; playfair_matrix[4][2] = 'w';
	playfair_matrix[4][3] = 'x'; playfair_matrix[4][4] = 'z';
	
	//string plaintext = "helloiambaymaxyourfriend";
	string plaintext = "meetmeattheschoxolhousex";
	string ciphertext = "";
	
	// create and initialize the integer equivalent
	// of the playfair matrix
	CPP_MATRIX playfair(5,5);
	
	for(unsigned i = 0; i < 5; i++)
	{
		for(unsigned j = 0; j < 5; j++)
		{
			playfair.set_matrix_entry(i,j, static_cast<int>(playfair_matrix[i][j]));
		}
	}
	
	unsigned subscript_x1 = 0;
	unsigned subscript_x2 = 0;
	unsigned subscript_y1 = 0;
	unsigned subscript_y2 = 0;
	
	for(unsigned i = 0; i < plaintext.length(); i+=2)
	{
		// search for corresponding coordinates of the 
		// current pair of plaintext letters
		for(unsigned j = 0; j < 5; j++)
		{
			for(unsigned k = 0; k < 5; k++)
			{
				if(playfair_matrix[j][k] == plaintext[i])
				{
					subscript_x1 = j;
					subscript_y1 = k;
				}
				if(playfair_matrix[j][k] == plaintext[i+1])
				{
					subscript_x2 = j;
					subscript_y2 = k;
				}
			}
		}
		
		if((subscript_x1 == subscript_x2) && (subscript_y1 != subscript_y2))
		{
			ciphertext += playfair_matrix[subscript_x1][(subscript_y1 + 1) % 5];
			ciphertext += playfair_matrix[subscript_x2][(subscript_y2 + 1) % 5];
		}
		else if((subscript_x1 != subscript_x2) && (subscript_y1 == subscript_y2))
		{
			ciphertext += playfair_matrix[(subscript_x1 + 1) % 5][subscript_y1];
			ciphertext += playfair_matrix[(subscript_x2 + 1) % 5][subscript_y2];
		}
		else if((subscript_x1 != subscript_x2) && (subscript_y1 != subscript_y2))
		{
			//E	3,1		T	4,5
			//M	3,5		N	4,1
			
			ciphertext += playfair_matrix[subscript_x1][subscript_y2];
			ciphertext += playfair_matrix[subscript_x2][subscript_y1];
		}
		
	}
	
	cout << "plaintext: " << plaintext << "\n";	
	cout << "ciphertext: " << ciphertext << "\n\n";
	
	return 0;
}
