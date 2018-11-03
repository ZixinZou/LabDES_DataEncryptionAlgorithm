#include <iostream>

using namespace std;

void displayBitTable(char *table, long tabsize) //每行四个形式显示表
{
	//cout << "Display in Binary / hexadecimal : ";
    for(long i=0; i < tabsize;i++)
    {
        cout << (int)table[i];

        if(((i+1)%4)==0)
        {
            cout << " ";
        }
    }
    cout << " / ";
}

void displayAsHex(char *table, long tabsize)
{
   long hexsize = tabsize/4; //转换成十六进制的长度
   char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i=0; i < hexsize;i++)
   {
       long value=0;

       for(long j=0; j <4; j++)
       {
            value = (2*value)+table[4*i+j];
       }

       cout << hexcodes[value];

        if(((i+1)%4)==0)
        {
            cout << " ";
        }
   }
   cout << endl;
}
