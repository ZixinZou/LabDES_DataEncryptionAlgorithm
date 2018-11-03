#include <iostream>
#include "subkey.h"
#include "bit_tables.h"

using namespace std;

void reverse(char *R, int i, int j) //逆置数组小标为i到第j的元素 
{
	char temp;
	for (; i<j; i++, j--)
	{
		temp = R[i];
		R[i] = R[j];
		R[j] = temp;
	}
}

char* subkey(char *table, char *pc_1_left,char *pc_1_right,int keyshift, char *pc_2,long tabsize)
{
	char *C0 = new char[28];
	char *D0 = new char[28];

	for (int i = 0; i <28; i++)
	{
		C0[i] = table[(int)pc_1_left[i] - 1];
	}
	for (int i = 0; i <28; i++)
	{
		D0[i] = table[(int)pc_1_right[i] - 1];
	}

	//char* CD[16];

		char *mc = new char[28];
		char *md = new char[28];
		for (int c = 0; c < 28; c++)
		{
			mc[c] = C0[c];
			md[c] = D0[c];
		}

		//keyshift
		reverse(mc, 0, keyshift - 1);
		reverse(mc, keyshift, 27);
		reverse(mc, 0, 27);

		reverse(md, 0, keyshift - 1);
		reverse(md, keyshift, 27);
		reverse(md, 0, 27);

		char *cd = new char[56];
		for (long j = 0; j < 56; j++)
		{
			if (j < 28)
				cd[j] = mc[j];
			else
				cd[j] = md[j - 28];
		}

		char *result = new char[48];

		for (int r = 0; r <48; r++)
		{
			result[r] = cd[(int)pc_2[r] - 1];
		}
		return result;
}