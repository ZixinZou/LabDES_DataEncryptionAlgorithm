#include "split.h"

char* splitting_l(char *table, long tabsize)
{
    char *result = new char[tabsize/2];

    for(int i=0; i <tabsize/2;i++)
    {
        result[i]=table[i]; 
    }

    return result;
}

char* splitting_r(char *table, long tabsize)
{
    char *result = new char[tabsize/2];

    for(int i=0; i <tabsize/2;i++)
    {
        result[i]=table[i+tabsize/2]; 
    }

    return result;
}
