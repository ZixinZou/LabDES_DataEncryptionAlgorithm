#ifndef ROUND_H_INCLUDED
#define ROUND_H_INCLUDED

char* round_l(char* ,char* ,long);
char* round_r(char* ,char* ,char* ,char* ,char[8][64],char*,long,long,int);
char* expand();
char* sbox(char*,char[8][64]);

#endif // ROUND_H_INCLUDED
