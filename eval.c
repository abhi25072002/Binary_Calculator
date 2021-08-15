#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "eval.h"
int preced(char c){
    if(c=='+' || c=='-')
        return 10;
    if(c=='*' || c=='/')
        return 20;
    if(c=='^')
        return 30;
    else
        return -1;
}
int isoperator(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^')
        return 1;
    else
        return 0;
}
void evaluate(char ch, stackv *s){
    number result;
    initn(&result);
    if(!isempty(*s)){
        number op1=pop(s);
        if(!isempty(*s)){
            number op2=pop(s);
            if(ch =='/')
                padding(&op1, &op2);
            switch(ch){
                case '+':
                    result=add(op1, op2);
                    break;
                case '-':
                    result=subtract(op2, op1);
                    break;
                case '*':
                    result=multiply(op1, op2);
                    break;
                case '^':
                    result=power(op2, op1);
                    break;
                case '/':
                    decimal(op2, op1, &result);
                    break;
            }
            push(s, result);
            return;
        }
        else{
            result.l=NULL;
            push(s,result);
            return;
        }

    }
    else{
        result.l=NULL;
        push(s, result);
        return;
    }
}
void expression(char *ex, stackv *s1, stackop *s2){
    int i=0,k,ob=0,cb=0;
    while(ex[i]!='\0'){
       if(ex[i]=='(')
            ob++;
       if(ex[i]==')')
            cb++;
       i++;
    }
    if(ob != cb){
        printf("Paranthesis is not balanced");
        printf("Error!");
        return;
    }
    i=0;
    while(ex[i]!='\0'){
        if(isdigit(ex[i])){
            int f=i+1;
            int m=0;
            number N1;
            initn(&N1);
            k = ex[i]-'0';
            giveno(&N1,k);
            while((ex[f]!=' ' && isdigit(ex[f])  && ex[f]!='\0')||(ex[f]=='.' && ex[f]!='\0')){
                m=m+1;
                if(isdigit(ex[f]))
                    giveno(&N1, ex[f]-'0');
                else if(ex[f]=='.'){
                    N1.decimalflag=1;
                    N1.decimalpos=m;
                }

                f++;
            }
            push(s1,N1);
            i=i+m+1;
            continue;
        }
        else if(ex[i]=='-' && isdigit(ex[i+1]) && ex[i+1]!='\0'){
            int f=i+2;
            int m=0;
            number N1;
            initn(&N1);
            N1.flag=1;
            k = ex[i+1]-'0';
            giveno(&N1, k);
            while((ex[f]!=' ' && isdigit(ex[f])  && ex[f]!='\0')||(ex[f]=='.' && ex[f]!='\0')){
                m=m+1;
                if(isdigit(ex[f]))
                    giveno(&N1, ex[f]-'0');
                else if(ex[f]=='.'){
                    N1.decimalflag=1;
                    N1.decimalpos=m;
                }

                f++;
            }
            push(s1, N1);
            i=i+m+2;
            continue;
        }
        else if(isoperator(ex[i])){
            if(isempty1(*s2)){
                push1(s2,ex[i]);
            }
            else{
                while((!isempty1(*s2))&&(preced(s2->a[s2->top])>=preced(ex[i]))){
                    char op1=pop1(s2);
                    evaluate(op1, s1);
                }
                push1(s2, ex[i]);
           }
        }
        else if(ex[i]=='(')
            push1(s2, ex[i]);
        else if(ex[i]==')'){
            while((!isempty1(*s2))&&((s2->a[s2->top])!='(')){
                char op1=pop1(s2);
                evaluate(op1, s1);
            }
            pop1(s2);
        }
        else if(ex[i]==' '){
        }
        else{
            printf("Error");
            return;
        }
        i++;
    }
    while(!isempty1(*s2)){
        char op2=pop1(s2);
        evaluate(op2, s1);
    }
}


