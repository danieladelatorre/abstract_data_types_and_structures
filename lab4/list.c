/*
Daniela De La Torre
Lab 4
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

typedef struct node{
        void *data;
        struct node *next;
        struct node *prev;
}NODE;

typedef struct list{
	int count;
	NODE *head;
	int (*compare)();
}LIST;

LIST *lp;

//Big O run time is O(1)
LIST *createList(int (*compare)()){
	LIST *lp = malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->compare=compare;
	lp->head=malloc(sizeof(NODE));
	assert(lp->head!=NULL);
	lp->count=0;
	lp->head->next = lp->head;	//initializes the dummy node and has it point to itself to make a circular doubly linked list
	lp->head->prev = lp->head;
	return lp;
}

//worst case Big O run time is O(n)
void destroyList(LIST *lp){
	assert(lp!=NULL);
	NODE *pDel, *pNext;
	pDel = lp->head;
	do{
		pNext = pDel->next;
		free(pDel);
		pDel=pNext;
	}while(pDel!=lp->head);	//traverses and frees all memory in the list
	free(lp);
	return;
}

//Big O run time is O(1)
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count; //returns how many elements are in the list
}

//Big O run time is O(1)
void addFirst(LIST *lp, void *item){
	assert(lp!=NULL);
	assert(item!=NULL);
	NODE *temp;
	temp = malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->data = item; //gives the new node's data the value of the data passed
	temp->next = lp->head->next;
	temp->prev = lp->head;
	lp->head->next->prev = temp;
	lp->head->next = temp;
	lp->count++;
	return;	
}

//Big O run time is O(1)
void addLast(LIST *lp, void *item){
	assert(lp!=NULL);
	assert(item!=NULL);
	NODE *temp;
	temp = malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->data = item;	//assigns data passed to the new node
	lp->head->prev->next = temp;
	temp->prev = lp->head->prev;
	temp->next = lp->head;
	lp->head->prev = temp;
	lp->count++;
	return;
}

//Big O run time is O(1)
void *removeFirst(LIST *lp){
	assert(lp!=NULL);
	NODE *pDel;
	void *value;
	pDel = lp->head->next;
	lp->head->next = pDel->next;
	pDel->next->prev = lp->head;
	value = pDel->data;
	free(pDel);	//removes first by reassigning the pointers and then freeing the first node
	lp->count--;	
	return value;
}

//Big O run time is O(1)
void *removeLast(LIST *lp){
	assert(lp!=NULL);
	NODE *pDel;
	void *value;
	pDel = lp->head->prev;
	pDel->prev->next=pDel->next;
	lp->head->prev = pDel->prev;
	value = pDel->data;
	free(pDel);	//reassigns pointers and then frees the node
	lp->count--;
	return value;
}

//Big O run time is O(1)
void *getFirst(LIST *lp){
	assert(lp!=NULL);
	return lp->head->next->data;	//returns information from first node
}

//Big O run time is O(1)
void*getLast(LIST*lp){
	assert(lp!=NULL);
	return lp->head->prev->data;	//returns information from last node
}

//worst case Big O run time is O(n)
void removeItem(LIST*lp, void*item){
	assert(lp!=NULL);
	assert(lp->compare!=NULL);
	assert(item!=NULL);
	NODE *pDel;
	pDel = lp->head->next;
	while(pDel!=lp->head){
		if((*lp->compare)(item, pDel->data)==0){	//if found, it frees the node
			pDel->prev->next = pDel->next;
			pDel->next->prev = pDel->prev;
			lp->count--;
			free(pDel);
		}
			pDel=pDel->next;
	}
	return;
	
}

//worst case Big O run time is O(n)
void*findItem(LIST*lp, void*item){
	assert(lp!=NULL);
	assert(lp->compare!=NULL);
	assert(item!=NULL);
	NODE *plocation;
	plocation = lp->head->next;
	while(plocation!=lp->head){
		if((*lp->compare)(item, plocation->data) != 0) 
			plocation = plocation->next;	//if not found it keeps traversing
		else 
			return plocation->data;
	}
	return NULL;
}

//worst case Big O run time is O(n)
void*getItems(LIST*lp){
	assert(lp!=NULL);
	void **copy;
	copy = malloc(sizeof(void*)*lp->count);
	assert(copy!=NULL);
	NODE *plocation = lp->head->next;
	int i=0;
	while(plocation!= lp->head){
		copy[i] = plocation->data;	//copies each data to each slot in copy
		i++;
		plocation = plocation->next;
	}
	return copy;			
}
