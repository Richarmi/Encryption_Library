// Program: ADFGX.cpp
// Programmer: Michael Richards
// Date: 2/25/16

#include <iostream>
#include <string>
#include "CPP_MATRIX_FUNCTIONS.h"
//#include "Encryption.h"
using namespace std;

/*****************************************************************************/

    struct ADFVGX_tuple
	{
		char letter;
		char x;
		char y;	
	};
	
	char alphabet[] = {'A','B','C','D','E','F','G','H','I','J',
	'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y',
	'Z','0','1','2','3','4','5','6','7','8','9'};


int main()
{
	char ADFGX[] = {'A','D','F','V','G','X'};
	ADFVGX_tuple alpha_pairs[36];
	
	// assign a corresponding pair to each alphabetical letter
	
	unsigned x = 0;
	unsigned y = 0;
	unsigned k = 0;
	
	for(unsigned i = 0; i < 6; i++)
	{
		for(unsigned j = 0; j < 6; j++)
		{
			alpha_pairs[k].letter = alphabet[k];
			alpha_pairs[k].x = ADFGX[i % 6];
			alpha_pairs[k].y = ADFGX[j % 6];  
			k++;
		}
	}
	
	
	
	string message = "HELLO I AM BAYMAX YOUR FRIEND";
	string ADFGX_message = "";
	string key = "RAINXZ";	
	
	for(unsigned i = 0; i < message.length(); i++)
	{
		for(unsigned j = 0; j < 26; j++)
		{
			if(alpha_pairs[j].letter == message[i])
			{
				ADFGX_message += alpha_pairs[j].x;
				ADFGX_message += alpha_pairs[j].y;
			}
		}
	}
	
	unsigned stuff_rows = ADFGX_message.length() / 6;
	CPP_MATRIX cipher_matrix(stuff_rows,6);
	
	// initialize the cipher matrix
	for(unsigned i = 0; i < stuff_rows; i++)
	{
		for(unsigned j = 0; j < 6; j++)
		{
			cipher_matrix.set_matrix_entry(i,j,0);
		}
	}
	
	cout << "Message: " << message << "\n\n";
	cout << "new message: " << ADFGX_message << "\n\n";
	
	
	// convert the letters of the original message
	// into numbers and place them in a matrix
	
	
	k = 0;
	
	for(unsigned i = 0; i < stuff_rows; i++)
	{
		for(unsigned j = 0; j < 6; j++)
		{
			unsigned temp = static_cast<unsigned>(ADFGX_message[k]);
			cipher_matrix.set_matrix_entry(i,j,temp);
			k++;
		}
	}
	
	cout << "Inputted matrix: " << "\n";
	cipher_matrix.output_matrix();
	
	// sort the key and make swaps to their
	// corresponding columns.
	int index_of_smallest = 0;
	cout << "\n" << "Original key: " << key << "\n";
	
	for(int i = 0; i < 5; i++)
	{
		if(key[i+1] <= key[i])
		{
			index_of_smallest = i + 1;
			column_swap(cipher_matrix, i, index_of_smallest);
			
			char temp = key[index_of_smallest];
			key[index_of_smallest] = key[i];
			key[i] = temp;		
		}
		else
		{
			index_of_smallest = i;
		}
	}
	
	cout << "Sorted key: " << key << "\n\n";
	
	cout << "sorted matrix: \n";
	
	cipher_matrix.output_matrix();
	
	
	// output the rows from first to last
	// to get the cipher.
	
	string cipher = "";
	
	for(unsigned i = 0; i < 6; i++)
	{
		for(unsigned j = 0; j < stuff_rows; j++)
		{
			cipher += static_cast<char>(cipher_matrix.get_matrix_entry(j,i));
		}	
	}
	
	cout << "Cipher-Text: " << cipher << "\n\n";
	
	return 0;
}
