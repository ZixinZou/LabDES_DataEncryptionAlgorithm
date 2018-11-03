#include "round.h"
#include "xor.h"
#include "sbox_helper.h"
#include "bit_tables.h"
#include "permutations.h"
#include <iostream>

using namespace std;

char *l1 = new char[32];
char *r1 = new char[32];
char *e_table1 = new char[48];
char *key_table1 = new char[48];
char s_tables[8][64];
long tabsize1=0;
long e_tabsize1=0;

char* round_l(char *l,char *r,long tabsize)
{
	char *result = new char[tabsize];
    for(int i=0; i <tabsize;i++)
    {
        result[i]=r[i]; 
    }
	return result;
}

char* round_r(char *l,char *r,char *e_table,char *keytable,char s_table[8][64],char *p_table, long tabsize,long e_tabsize,int fois)
{
	for(int i=0; i <tabsize;i++)
    {
        r1[i]=r[i]; 
    }
	for(int i=0; i <tabsize;i++)
    {
        l1[i]=l[i]; 
    }
	e_table1=e_table;
	tabsize1=tabsize;
	e_tabsize1=e_tabsize;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<64;j++)
		{
			s_tables[i][j]=s_table[i][j];
		}
	}
	for(int i=0;i<48;i++)
	{
		key_table1[i]=keytable[i];
	}

	r1=expand();
	r1=xor(r1,keytable,e_tabsize1);
	r1=sbox(r1,s_tables);
	r1=permute(r1,p_table,tabsize);
	r1=xor(r1,l1,tabsize);
	return r1;
}

char* expand()
{
	char *result = new char[e_tabsize1];

    for(int i=0; i <e_tabsize1;i++)
    {
        result[i]=r1[(int)e_table1[i]-1];
    }

    return result;
}

char* sbox(char *table,char s_table[8][64])
{
	char *result = new char[e_tabsize1];
	for(int i=0;i<8;i++)
	{
		char *t = new char[6];//chaque block
		char *s = new char[64];//s-table
		char *line_char = new char[2];
		char *row_char = new char[4];
		int line_int=0;
		int row_int=0;
		int s_box=0;
		char *r = new char[4];
		for(int j=0;j<6;j++)
		{
			t[j]=table[i*6+j];
		}
		for(int y=0;y<64;y++)
		{
			s[y]=s_table[i][y];
		}
		line_char[0] =  t[0];
		line_char[1] =  t[5];
		row_char[0] = t[1];
		row_char[1] = t[2];
		row_char[2] = t[3];
		row_char[3] = t[4];
		line_int=generateIntFromBitBlock(line_char,2);
		row_int=generateIntFromBitBlock(row_char,4);
		s_box=s_table[i][line_int*16+row_int];
		r=generateBitBlockFromInt(s_box);
		for(int p=0;p<4;p++)
		{
			result[i*4+p]=r[p];
		}
	}
	//cout << "****\n";
	//displayBitTable(result,32);
	//cout << "****\n";
    return result;
}

