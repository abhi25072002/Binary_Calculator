#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "numbers.h"
typedef struct stack{
    number *a;
    int top;
    int length;
}stackv;
typedef struct stack1{
    char *a;
    int top;
    int length;
}stackop;
void inits(stackv *s, int len);
void push(stackv *s, number a);
number pop(stackv *s);
int isempty(stackv s);
int isfull(stackv s);
void init1(stackop *s, int len);
void push1(stackop *s, char d);
char pop1(stackop *s);
int isempty1(stackop s);
int isfull1(stackop s);
#endif // STACK_H_INCLUDED
