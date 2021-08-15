#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
void inits(stackv *s, int len){
    s->a=(number *)malloc((sizeof(number))*len);
    s->length=len;
    s->top=-1;
}
void init1(stackop *s, int len){
    s->a=(char *)malloc(sizeof(char)*len);
    s->length=len;
    s->top=-1;
}
int isempty(stackv s){
    if(s.top==-1)
        return 1;
    else
        return 0;
}
int isempty1(stackop s){
    if(s.top==-1)
        return 1;
    else
        return 0;
}
int isfull(stackv s){
    if(s.top==s.length-1)
        return 1;
    else
        return 0;
}
int isfull1(stackop s){
    if(s.top==s.length-1)
        return 1;
    else
        return 0;
}
void push(stackv *s,number a){
    if(isfull(*s)){
       return;
    }
    s->top++;
    s->a[s->top]=a;
    return;
}
void push1(stackop *s, char d){
    if(isfull1(*s)){
       return;
    }
    s->top++;
    s->a[s->top]=d;
    return;
}
number pop(stackv *s){
    number N1;
    initn(&N1);
    if(isempty(*s))
        return N1;
    return s->a[s->top--];
}
char pop1(stackop *s){
    if(isempty1(*s))
        return '#';
    return s->a[s->top--];
}
