#include <iostream>
#include "permutations.h"
#include "bit_tables.h"
#include "data_tables.h"
#include "data_messages_examples.h"
#include "split.h"
#include "round.h"
#include "subkey.h"

using namespace std;

int main()
{
    char *firstperm;    //初始顺序
	char *l;//分离后的左部分
	char *r;
	char *temp = new char[32];
	char* subkeys;
	char full_subkeys[16][48]={};
	cout<<"MESSAGE:"<<endl;
    displayBitTable(message_03,64); //显示表
    displayAsHex(message_03,64);  //转换成十六进制输出
	cout<<endl;
	cout<<"KEY:"<<endl;
	displayBitTable(globalkey,64);
    displayAsHex(globalkey,64); 
	cout<<endl;

    firstperm=permute(message_03,init_perm,64);//替换
	l=splitting_l(firstperm,64);
	r=splitting_r(firstperm,64);
	int count=15;

	for (int i = 0; i < 16; i++)
	{
		subkeys = subkey(globalkey, pc_1_left, pc_1_right, (int)keyshift[i], pc_2, 64);
		for(int j=0;j<48;j++)
		{
			full_subkeys[count][j]=(int)subkeys[j];
		}
		cout <<"ROUND:"<<i+1<<endl;
		cout <<"SUBKEY "<<": ";
		displayBitTable(subkeys,32);
		displayAsHex(subkeys,32);
		cout <<"L      "<<": ";
		displayBitTable(l,32);
		displayAsHex(l,32);
		cout <<"R      "<<": ";
		displayBitTable(r,32);
		displayAsHex(r,32);
		cout<<endl;
		temp=round_l(l,r,32);
		r=round_r(l,r,expansion_table,subkeys,s_boxes,permut_32,32,48,i);
		l=round_l(l,temp,32);
		count--;
	}
	cout<<endl;
	char *final = new char[64];
	for(int j=0;j<64;j++)
	{
		if(j<32)
		{
			final[j]=r[j];
		}
		else
		{
			final[j]=l[j-32];
		}
	}
	cout<<"JOINING L16+R16: "<<endl;
	displayBitTable(final,64); 
    displayAsHex(final,64);   
	cout<<endl;
	final=permute(final,reverse_perm,64);
	cout<<"ENCRYPTED MESSAGE: "<<endl;
    displayBitTable(final,64); 
    displayAsHex(final,64);  
	cout<<endl;

	//解密
	char *decrypt = new char[64];
	decrypt=permute(final,init_perm,64);//替换
	l=splitting_l(decrypt,64);
	r=splitting_r(decrypt,64);
	for (int i = 0; i < 16; i++)
	{
		char *de_subkeys = new char[64];
		for(int j=0;j<48;j++)
		{
			de_subkeys[j]=full_subkeys[i][j];
		}
		temp=round_l(l,r,32);
		r=round_r(l,r,expansion_table,de_subkeys,s_boxes,permut_32,32,48,i);
		l=round_l(l,temp,32);
	}
	for(int j=0;j<64;j++)
	{
		if(j<32)
		{
			decrypt[j]=r[j];
		}
		else
		{
			decrypt[j]=l[j-32];
		}
	}
	decrypt=permute(decrypt,reverse_perm,64);
	cout<<"DECRYPTED MESSAGE: "<<endl;
    displayBitTable(decrypt,64); //输出结果表
    displayAsHex(decrypt,64); 
	system("pause");
}
