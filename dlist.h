#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED
typedef struct node{
    int data;
    struct node *prev;
    struct node *next;
}node;
typedef node *dlist;
void init(dlist *l);
void append(dlist *l, int data);
void insert_at(dlist *l, int data);
void display(dlist l, int dpos, FILE *fp);
int length(dlist l);
node *lastptr(dlist l);
int equal(dlist l1, dlist l2);
int greater(dlist l1, dlist l2);
void delete1(dlist *l);
void delete_at(dlist *l);
#endif // DLIST_H_INCLUDED
