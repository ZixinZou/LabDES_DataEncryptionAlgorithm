#include "xor.h"

char* xor(char *table, char *keytable, long tabsize)
{

    for(int i=0; i <tabsize;i++)
    {
        table[i] ^= keytable[i]; 
    }

    return table;
}