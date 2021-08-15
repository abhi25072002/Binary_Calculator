#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED
#include "dlist.h"
typedef struct number{
    dlist l;
    int flag;
    int decimalflag;
    int decimalpos;
}number;
typedef number *num;
void initn(num N1);
void giveno(num N1, int data);
number add(number N1, number N2);
number subtract(number N1, number N2);
number multiply(number N1, number N2);
number multiply_sdigit(number N1, int dig);
void padding(num N1, num N2);
int equalto(number N1, number N2);
int greaterthan(number N1, number N2);
void putno(number N1,FILE *fp);
void destroy(num N1);
number power(number a, number b);
int equaltozero(number N1);
void divideby(number N1, number N2, num N3);
void dividedecimal(number N1, number N2, num N3);
void decimal(number N1,number N2,num N3);
#endif // NUMBERS_H_INCLUDED
