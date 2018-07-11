// Program: 	Vigenere.cpp
// Programmer:	Michael Richards
// Date:		7/11/18

#include<iostream>
#include<string>
using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !?;:-~";

int Alphabet_Encode(char this_char, string character_list)
{
	for(int i = 0; i < character_list.length(); i++)
	{
		if(character_list[i] == this_char)
		{
			return i;
			break;
		}
	}
}

/*****************************************************************************/

char Alphabet_Decode(int this_integer, string character_list)
{
	if((this_integer >= 0) && (this_integer < character_list.length())) { return character_list[this_integer]; }
}

void Vigenere(string& message, int message_size, int key[], int key_size)
{
    char temp_a;
    int temp_b;
    int num = 0;

    for(int i = 0; i < message_size; i++)
    {
        //convert the ith char of message to a number
        temp_a = message[i];
        temp_b = Alphabet_Encode(temp_a, alphabet);
        temp_b += key[i % key_size] % 90;

        //convert it back into a char and place at
        //the ith position of the message.
        temp_a = Alphabet_Decode(temp_b, alphabet);
        message[i] = temp_a;
    }
}



int main()
{
	
	string vigenere_plain = "hi there";
	string vigenere_cipher = "";
	int vigenere_key[] = {2,9,4,8};
	int vigenere_len = 4;
	
	Vigenere(vigenere_plain, vigenere_plain.length(), vigenere_key, vigenere_len);
	
	return 0;
}
