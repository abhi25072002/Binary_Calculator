#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "dlist.h"
void init(dlist *l){
    *l=NULL;
    return;
}
void append(dlist *l, int d){
    node *p=(dlist)malloc(sizeof(node));
    p->data=d;
    p->prev=p->next=NULL;
    node *a=*l;
    if(*l==NULL){
        *l=p;
        return;
    }
    while(a->next!=NULL){
        a=a->next;
    }
    a->next=p;
    p->prev=a;
    return;
}
void insert_at(dlist *l, int d){
    node *p=(dlist)malloc(sizeof(node));
    p->data=d;
    p->prev=p->next=NULL;
    node *a=*l;
    if(*l==NULL){
        *l=p;
        return;
    }
    p->next=a;
    a->prev=p;
    *l=p;
    return;
}
int length(dlist l){
    node *p=l;
    int len=0;
    if(p==NULL){
        return 0;
    }
    while(p){
        p=p->next;
        len++;
    }
    return len;
}
node *lastptr(dlist l){
    node *p=l;
    if(!p)
        return NULL;
    else{
        while(p->next!=NULL){
            p=p->next;
        }
        return p;
    }
}
int greater(dlist l1, dlist l2){
    node *a=l1;
    node *b=l2;
    int j=0;
    if(a->data > b->data){
        return 1;
    }
    else if(a->data < b->data){
        return 0;
    }
    else{
        while(a && b){
            if(a->data > b->data){
                return 1;
            }
            else if(a->data < b->data){
                return 0;
            }
            else
                j=0;
            a=a->next;
            b=b->next;
        }
        return j;
    }
}
int equal(dlist l1, dlist l2){
    node *a=l1;
    node *b=l2;
    int l=length(l1);
    int m=length(l2);
    int ct1=0,ct2=0;
    while(a && (a->data==0)){
        ct1++;
        a=a->next;
    }
    while(b  && b->data==0){
        ct2++;
        b=b->next;
    }
    while(a && b){
        if(a->data==b->data){
            ct1++;
            ct2++;
        }
        a=a->next;
        b=b->next;
    }
    if(ct1==l && ct2==m)
        return 1;
    else
        return 0;
}
void display(dlist l, int dpos, FILE *fp){
    if(l==NULL)
        return;
    if(dpos==-1){    //If number doesnot contain decimal point,proceed with this aprt
        node *p=l;
        while(p){
            if(p->data!=0)
                break;
            else{
                p=p->next;
                continue;
            }
        }
        while(p){
            printf("%d", p->data);
            fprintf(fp,"%d", p->data);
            p=p->next;
        }
        return;
    }
    else{
        int i=0;
        int k=0;
        int j=0;
        node *p=l;
        node *q=l;
        while (q){
            if(q->data==0 && j < dpos){
                j++;
                k=1;
                q=q->next;
                continue;
            }
            if(q->data!=0 && j< dpos){
                k=0;
                break;
            }
            else
                break;
        }
        if(k==0){
                if(dpos==1 && p->data==0){  //If result is 0.0004 u should print that 0 and p should now point to significant zero
                    printf("%d", p->data);
                    fprintf(fp,"%d", p->data);
                    p=p->next;
                    i++;
                }
                else{
                    while(p){
                        if(p->data==0){       //else suppose we have 0180.0 then we need to skip all leading 0s so till we encountered 0 ignore that at same time dpos should be reduced each time as in 00180.0,0 sapadla dpos should be now 3,
                            dpos--;
                            p=p->next;
                            continue;
                        }
                        else
                            break;
                    }
                }
        }
        while(p && i<dpos){
            printf("%d", p->data);
            fprintf(fp, "%d", p->data);
            p=p->next;
            i++;
        }
        q=p;
        i=0;
        j=0;
        while(q){
            if(q->data!=0)
                i++;
            q=q->next;
        }
        if(i==0)
            return;
        printf(".");
        fprintf(fp, ".");
        while(p){
            if(p->data!=0){
                if(j < i){
                    j++;
                    printf("%d", p->data);
                    fprintf(fp, "%d",p->data);
                    if(j==i)
                        return;
                    p=p->next;
                    continue;
                }
                else
                    break;
            }
            printf("%d", p->data);
            fprintf(fp, "%d", p->data);
            p=p->next;
        }
        return;
    }
    return;
}
void delete1(dlist *l){
    if(*l==NULL)
        return;
    node *p=*l;
    node *a=*l;
    while(p){
        a=p;
        p=p->next;
        free(a);
    }
    *l=NULL;
    return;
}
void delete_at(dlist *l){
    if(*l==NULL)
        return;
    else{
        node *p=*l;
        node *a=p;
        if(!(p->next)){
            free(p);
            *l=NULL;
            return;
        }
        else{
            p->next->prev=NULL;
            p=p->next;
            *l=p;
            free(a);
            return;
        }
    }
    return;
}
