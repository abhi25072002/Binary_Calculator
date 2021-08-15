#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED
#include "stack.h"
int preced(char c);
int isoperator(char c);
void evaluate(char ch,stackv *s);
void expression(char *ex,stackv *s1,stackop *s2);
#endif // EVAL_H_INCLUDED
