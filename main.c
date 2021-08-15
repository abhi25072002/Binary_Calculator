#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eval.h"
int main(){
    char ex[1000];
    stackv s1;
    number N5;
    initn(&N5);
    stackop s2;
    inits(&s1, 100);
    init1(&s2, 100);
    FILE *fp;
    fp=fopen("E:/SYBTECH SEM 1/BCalculator_Project/History1.txt","a");
    while(1){
        printf(">>>>");
        fprintf(fp, ">>>>");
        fflush(stdin);
        gets(ex);
        fprintf(fp, "%s", ex);
        if(ex[0]=='q'){
            fprintf(fp, "\n");
            break;
        }
        expression(ex, &s1, &s2);
        N5=pop(&s1);
        if(!(N5.l)){
            printf("Error");
            fprintf(fp, "\nError\n");
        }
        else{
            fprintf(fp, "\n");
            putno(N5, fp);
            destroy(&N5);
        }
        printf("\n");
        fprintf(fp, "\n");
    }
    return 0;
}
