#include<stdio.h>
#include<stdlib.h>
#include "numbers.h"
void initn(num  N1){
    N1->decimalflag=0;
    N1->flag=0;
    N1->decimalpos=-1;
    init(&(N1->l));
    return;
}
void giveno(num N1, int data){
    append(&(N1->l), data);
    return;
}
void putno(number N1, FILE *fp){
    if(equaltozero(N1)){
        printf("0");
        fprintf(fp, "0");
        return;
    }
    if(N1.flag==1){
        printf("-");
        fprintf(fp, "-");
    }
    if(N1.decimalflag==0){
        display(N1.l, -1, fp);
    }
    else{
        display(N1.l, N1.decimalpos, fp);
    }
    return;
}
int greaterthan(number N1, number N2){
    return greater(N1.l, N2.l);
}
int equalto(number N1, number N2){
    return equal(N1.l, N2.l);
}
void destroy(num N1){
    delete1(&(N1->l));
    return;
}
int equaltozero(number N1){
    node *a=N1.l;
    while(a){
        if((a->data)!=0)
            return 0;
        else
            a=a->next;
    }
    return 1;
}
void padding(num N1, num N2){
    if(N1->decimalflag ==1 && N2->decimalflag ==1){
        if(N1->decimalpos > N2->decimalpos){
            for(int i=0; i<(N1->decimalpos - N2->decimalpos); i++){
                    insert_at(&(N2->l), 0);
            }
            N2->decimalpos=N1->decimalpos;
        }
        else if(N1->decimalpos < N2->decimalpos){
            for(int i=0; i<(N2->decimalpos - N1->decimalpos); i++){
                insert_at(&(N1->l), 0);
            }
            N1->decimalpos=N2->decimalpos;
        }
        int a=(length(N1->l) - N1->decimalpos);
        int b=(length(N2->l) - N2->decimalpos);
        if(a>b){
            for(int i=0; i<(a-b); i++){
                append(&(N2->l), 0);
            }
        }
        else if(b>a){
            for(int i=0; i<(b-a); i++){
                append(&(N1->l), 0);
            }
        }
    }
    else if(N1->decimalflag==0 && N2->decimalflag==1){
        int a=length(N1->l);
        int b=length(N2->l) - (N2->decimalpos);
        if(a > N2->decimalpos){
            for(int i=0; i<(a-(N2->decimalpos)); i++){
                insert_at(&(N2->l), 0);
            }
            N2->decimalpos=a;
        }
        else{
            for(int i=0; i<((N2->decimalpos) - a); i++){
                insert_at(&(N1->l), 0);
            }
        }
        N1->decimalpos=length(N1->l);
        N1->decimalflag=1;
        for(int i=0; i < b; i++){
            append(&(N1->l), 0);
        }

    }
     else if(N1->decimalflag==1 && N2->decimalflag==0){
        int a=length(N2->l);
        int b=length(N1->l) - (N1->decimalpos);
        if(a > N1->decimalpos){
            for(int i=0;i<(a-(N1->decimalpos));i++){
                insert_at(&(N1->l),0);
            }
            N1->decimalpos=a;
        }
        else{
            for(int i=0;i<((N1->decimalpos) - a);i++){
                insert_at(&(N2->l),0);
            }
        }
        N2->decimalpos=length(N2->l);
        N2->decimalflag=1;
        for(int i=0;i < b;i++){
            append(&(N2->l),0);
        }

    }
    else{
        int a=(length(N1->l) > length(N2->l))?length(N1->l)-length(N2->l):length(N2->l)-length(N1->l);
        if(length(N1->l) > length(N2->l)){
            for(int i=0;i<a;i++){
                insert_at(&(N2->l),0);
            }
        }
        else{
            for(int i=0;i<a;i++){
                insert_at(&(N1->l),0);
            }
        }
    }
}
number add(number N1, number N2){   //1234 + 22   1234 + 0022
    number N3;
    initn(&N3);
    if((!(N2.l))||(!(N1.l))){
        N3.l=NULL;
        return N3;
    }
    padding(&N1,&N2);
    if((N1.flag==1 && N2.flag==1)||(N2.flag==0 && N1.flag==0)){
        int carry=0, a1=0;
        int result=0;
        node *a=lastptr(N1.l);
        node *b=lastptr(N2.l);
        while(a && b){
            result=a->data + b->data + carry;
            if((result/10)>=1){
                a1=result%10;
                carry=result/10;
            }
            else{
                a1=result;
                carry=0;
            }
            insert_at((&N3.l), a1);
            a=a->prev;
            b=b->prev;
        }
        if(carry!=0){
            insert_at((&N3.l), carry);
        }
        N3.decimalflag=N1.decimalflag;
        N3.decimalpos=(carry!=0)?(N2.decimalpos+1):N2.decimalpos;
        N3.flag=N1.flag;
        return N3;
    }
    else{
        if(N1.flag==1 && N2.flag==0){   //-3 + 4
            N1.flag=0;
            N3=subtract(N2, N1);
            N1.flag=1;
            return N3;
        }
        else{        //  4 + -3
            N2.flag=0;
            N3=subtract(N1, N2);
            N2.flag=1;
           return N3;
        }

    }
}
number subtract(number N1, number N2){
    number N3;
    initn(&N3);
     if((!(N2.l))||(!(N1.l))){
        N3.l=NULL;
        return N3;
    }
    padding(&N1, &N2);
    if(N1.flag==0 && N2.flag==0){     //40 - 38
        node *a=lastptr(N1.l);
        node *b=lastptr(N2.l);
        int borrow=0;
        int result=0;
        if(greaterthan(N1, N2)){   //See if 40 is greater than 38
            while(a && b){
                if(a->data>=(b->data+borrow)){
                    result=a->data-(b->data+borrow);
                    borrow=0;
                }
                else if(a->data<(b->data+borrow)){
                    result=10+a->data-(b->data+borrow);
                    borrow=1;
                }
                insert_at(&(N3.l), result);
                a=a->prev;
                b=b->prev;
            }

        }
        else if(equalto(N1, N2)){  //IF equal simply give 0
            for(int i=0; i<length(N1.l); i++){
                insert_at(&(N3.l), 0);
            }
            return N3;
        }
        else{
            while(a && b){
                if(b->data>=(a->data+borrow)){
                    result=b->data-(a->data+borrow);  //else subtract 2 nd no from first
                    borrow=0;
                }
                else if(b->data<(a->data+borrow)){
                    result=10+b->data-(a->data+borrow);
                    borrow=1;
                }
                insert_at(&(N3.l), result);
                a=a->prev;
                b=b->prev;
            }
            N3.flag=1;
        }
        N3.decimalflag=N1.decimalflag;
        N3.decimalpos=N2.decimalpos;
        return N3;
    }
    else if(N1.flag==0 && N2.flag==1){   //2 - -2
        N2.flag=0;
        N3=add(N1, N2);
        N2.flag=1;
        return N3;
    }
    else if(N1.flag==1 && N2.flag==0){  //-2 - 2
        N2.flag=1;
        N3=add(N1, N2);
        N2.flag=0;
        return N3;
    }
    else{
        N1.flag=0;
        N2.flag=0;
        N3=subtract(N2, N1);
        N1.flag=N2.flag=1;
        return N3;
    }
}
number multiply_sdigit(number N1, int dig){
    number N3;
    initn(&N3);
    int k=length(N1.l);
    for(int i=1; i<=k; i++){
            append(&(N3.l), 0);
    }
    if(dig==0){
        return N3;
    }
    else{
        while(dig!=0){
            N3=add(N3, N1);
            dig=dig-1;
        }
        return N3;
    }

}
number multiply(number N1, number N2){
    number N3;
    initn(&N3);
     if((!(N2.l))||(!(N1.l))){
        N3.l=NULL;
        return N3;
    }
    number N4;
    initn(&N4);
    int f1=N1.flag;
    int f2=N2.flag;
    N1.flag=0;
    N2.flag=0;
    int df1=N1.decimalflag;
    int df2=N2.decimalflag;
    int dp1=length(N1.l)-((df1==1)?(N1.decimalpos):length(N1.l));   //Calculating digits after which decimal point should be there in final result
    int dp2=length(N2.l)-((df2==1)?(N2.decimalpos):length(N2.l));
    N1.decimalflag=0;
    N2.decimalflag=0;
    for(int k=1; k<=length(N1.l); k++){
        append(&(N4.l), 0);
    }
    int i=0;
    int len=length(N2.l);
    node *b=lastptr(N2.l);
    while(b && i<len){
        N3=multiply_sdigit(N1,b->data);   //Reduced number of multiplications.
        for(int j=0; j<i; j++){
            append(&(N3.l), 0);
        }
        N4=add(N4, N3);
        i++;
        b=b->prev;
    }
    if(f1+f2==1){
        N4.flag=1;
    }
    else{
        N4.flag=0;
    }
    N1.flag=f1;
    N2.flag=f2;
    if((df1+df2)!=0){   //-3 * 4
        N4.decimalflag=1;
        N4.decimalpos=(length(N4.l)- dp1 - dp2);
        N1.decimalflag=df1;
        N2.decimalflag=df2;
    }
    else{
        N4.decimalflag=0;
        N4.decimalpos=-1;
    }
    return N4;
}
number power(number a, number b){   //Also handled negative exponents
    number N1, N2, N3, N4, N5;
    initn(&N1);
    initn(&N2);
    initn(&N3);
    initn(&N4);
    initn(&N5);
    append(&(N3.l), 1);
    N4=N3;
    N1=a;
    append(&(N2.l), 0);
    padding(&N2, &b);
    if(equalto(N2, b)){
        return N3;
    }
    N1=multiply_sdigit(N1, 1);
    append(&(N2.l), 1);
    padding(&N2, &b);
    while(!(equalto(N2, b))){
        N1=multiply(N1, a);
        N2=add(N2, N3);
    }
    if(b.flag==1){
        dividedecimal(N4,N1,&N5);
        return N5;
    }
    return N1;

}
void divideby(number N1, number N2, num N3){   //128/8
    if(equaltozero(N2)){
        N3=NULL;
        N3->l=NULL;
        printf("Divide by zero Error\n");
        return;
    }
    int f1=N1.flag;
    int f2=N2.flag;
    N1.flag=N2.flag=0;
    number N4,N5,N6;
    initn(&N4);
    initn(&N5);
    initn(&N6);
    node *a=N1.l;
    while(a){
        if(a->data==0){
            a=a->next;
        }
        else
            break;
    }
    while(a){
        append(&(N4.l), a->data);
        padding(&N4, &N2);
         if(equaltozero(N4)){   //Here itself if N4 is equal to 0 then append 0 (7686/6)
            append(&(N6.l), 0);
            a=a->next;
            continue;
        }
        int m=9;
        while(m >=0 ){
            N5=multiply_sdigit(N2, m);
            padding(&N5, &N4);
            if(equalto(N5, N4)){
                N4=subtract(N5, N4);
                append(&(N6.l), m);
                break;
            }
            if(greaterthan(N5, N4)){
                m=m-1;
                if(m==0){
                    append(&(N6.l), 0);
                    break;
                }
                continue;
            }
            else{
                N4=subtract(N4, N5);
                append(&(N6.l), m);
                break;
            }

        }
        a=a->next;
    }
    if(f1+f2==1){
        N6.flag=1;
        N1.flag=f1;
        N2.flag=f2;
    }
    else{
        N6.flag=0;
        N1.flag=f1;
        N2.flag=f2;
    }
    *N3=N6;
    return;
}
void dividedecimal(number N1, number N2, num N3){   //23/34 || 45/34
    if(equaltozero(N2)){
        printf("Divide by zero error !");
        N3->l=NULL;
        return;
    }
    if(equaltozero(N1)){
        append(&(N3->l), 0);
        return;
    }
    number N5,N7,N8,N9;
    int ct1=0,ct2=0;
    initn(&N5);
    initn(&N7);
    initn(&N8);
    initn(&N9);
    int len1=length(N1.l);
    int len2=length(N2.l);
    N7=N1;
    N8=N2;
    padding(&N1, &N2);
    if(equalto(N1, N2)){
        append(&(N3->l), 1);
        return;
    }
    if(greaterthan(N1, N2)){
         divideby(N1, N2, &N5);
         node *p=N5.l;
         int m=length(N5.l);
         while(p){
            if(p->data==0){
                p=p->next;
                ct1++;
            }
            else
                break;
        }
        m=m-ct1;
        for(int i=0; i<(len1-len2+10); i++){
            append(&(N7.l), 0);
        }
        divideby(N7, N8, N3);
        node *h=N3->l;
        while(h){
            if(h->data==0){
                h=h->next;
                ct2++;
            }
            else
                break;
        }
        N3->decimalflag=1;
        N3->decimalpos=ct2+m;
    }
    else{
        int k=0;
        padding(&N7, &N8);
        while(!greaterthan(N7, N8)){
            if(equalto(N7,N8)){
                break;
            }
            k++;
            append(&N7.l, 0);
            padding(&N7, &N8);
        }
         for(int i=0; i<6; i++){
            append(&(N7.l), 0);
        }
        divideby(N7, N8, N3);
        node *q=N3->l;
        while(q){
            if(q->data==0){
                delete_at(&(N3->l));
                q=q->next;
                continue;
            }
            else
                break;
        }
        for(int i=0; i<k; i++){
            insert_at(&(N3->l),0);
        }
        N3->decimalpos=1;
        N3->decimalflag=1;
    }
}
void decimal(number N1, number N2, num N3){
    if(N1.flag==1 && N2.flag==1){
        N3->flag=0;
    }
    else if (N1.flag+N2.flag){
        N3->flag=1;
    }
    int dp1=N1.decimalpos;
    int dp2=N2.decimalpos;
    int f1=N1.decimalflag;
    int f2=N2.decimalflag;
    int lend1=length(N1.l)-dp1;
    int lend2=length(N2.l)-dp2;
    int c=lend1-lend2;
    N1.decimalflag=N2.decimalflag=0;
    N1.decimalpos=-1;
    N2.decimalpos=-1;
    dividedecimal(N1, N2, N3);
    if(!N3){
        N1.decimalpos=dp1;
        N2.decimalpos=dp2;
        N1.decimalflag=f1;
        N2.decimalflag=f2;
        return;
    }
    if(c>=0){
        for(int i=0;i<c;i++){
            insert_at(&(N3->l), 0);
        }
        N3->decimalflag=1;
        if(equalto(N1, N2)){  //For numbers like 0.5000/0.05
            N3->decimalpos=1;
        }
    }
    else{
        N3->decimalpos=N3->decimalpos-c;
        N3->decimalflag=1;
    }
    N1.decimalpos=dp1;
    N2.decimalpos=dp2;
    N1.decimalflag=f1;
    N2.decimalflag=f2;
    return;
}

