#include "permutations.h"

char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize]; //结果

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table[(int)perm_table[i]-1]; //perm_table表中的值是table表中的位置下标
    }

    return result;
}
