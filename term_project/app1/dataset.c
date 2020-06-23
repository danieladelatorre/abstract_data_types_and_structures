#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "list.h"
#define LENGTH 13
#define EMPTY 0
#define FILLED 2

typedef struct set{
	int length;
	int count;
	int size;
	LIST **lists;
	char *flag;
}SET;

SET *sp;

typedef struct node{
	int age;
	int id;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct list{
	int counts;
	NODE *head;
}LIST;

LIST *lp;

//worst case Big O is O(1)
LIST *createList(){
	LIST *lp = malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->head = malloc(sizeof(NODE));
	assert(lp->head!=NULL);
	lp->counts=0;
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

//worst case Big O is O(n)
SET *createDataSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->length = maxElts;
	sp->size = LENGTH;
	sp->count = 0;	
	sp->lists = malloc(sizeof(LIST)*sp->size);
	sp->flag = malloc(sizeof(char)*LENGTH);
	for(int i=0; i<LENGTH; i++){
		sp->lists[i] = createList();
		sp->flag[i] = EMPTY;
	}
	return sp;
}

//this function deletes the list pointed to
//worst case Big O is O(n)
void destroyList(LIST *lp){
	assert(lp!=NULL);
	NODE *pDel, *pNext;
	pDel = lp->head;
	do{
		pNext = pDel->next;
		free(pDel);
		pDel=pNext;
	}while(pDel!=lp->head);
	free(lp);
	return;
}

//deletes all entries in the data set
//worst case Big O is O(n) including the destroyList function
void destroyDataSet(SET *sp){
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->size;i++){	//goes through array and if its not empty it deletes the list
		if(sp->flag[i] == FILLED){
			destroyList(sp->lists[i]);
		}
	}
	free(sp->lists);
	free(sp);
	return;
}

//passes the position of the age group to the searchAge function
//worst case Big O is O(n) including the searchAge function and O(1) not including it
void findAge(SET *sp, int age){
	assert(sp!=NULL);
	int position = age-18;
	searchAge(sp->lists[position]);	//calls searchAge function to find the student and print information
	return;
}

//returns all entries with the specified age
//worst case Big O is O(n) 
void searchAge(LIST *lp){
	assert(lp!=NULL);
	void **copy;
	copy = malloc(sizeof(void*)*(lp->counts));
	assert(copy!=NULL);
	NODE *plocation = lp->head->next;
	while(plocation!=lp->head){	//prints student information and if found
		printf("student with age: %d and id: %d has been found\n", plocation->age, plocation->id);	//prints all student information with the specified age
		plocation = plocation->next;
	}
	return;
}

//worst case Big O is O(1)
void addFirst(LIST *lp, int id, int age){
	assert(lp!=NULL);
	NODE *temp;
	temp = malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->age = age;
	temp->id = id;
	temp->next = lp->head->next;
	temp->prev = lp->head;
	lp->head->next->prev = temp;
	lp->head->next = temp;
	lp->counts++;
	return;
} 

//inserts the information of the new student
//worst case Big O is O(1) including the addFirst function
void insertion(SET *sp, int id, int age){
	assert(sp!=NULL);
	int position;
	position = age-18;
	if(sp->count == sp->length){	//if full it returns 
		printf("no more space available\n");
		return;
	}
	else{
		addFirst(sp->lists[position], id, age);
		sp->count++; 
		sp->flag[position] = FILLED;	//updates the parallel array to make sure its filled
	} 
	return;
}

//deletes all records with the given age
//worst case Big O is O(n) including the removeRow function
void deletion(SET *sp, int age){
	assert(sp!=NULL);
	int position, delete;
	position = age-18;
	delete = removeRow(sp->lists[position]);	//calls the removeRow function to delete the entire row
	sp->count -= delete;	//must update the total number of elements in the set 
	sp->flag[position] = EMPTY;
	printf("successfully deleted entries with age %d\n", age);
	return;
}

//worst case Big O is O(n)
int removeRow(LIST *lp){
	assert(lp!=NULL);
	int deleted_elements=0;
	NODE *pDel, *pNext;
	pDel = lp->head->next;
	while(pDel!=lp->head){
		printf("student with age: %d and id: %d has been deleted\n", pDel->age, pDel->id);	//prints the information of the students being deleted
		pNext = pDel->next;
		free(pDel);
		pDel = pNext; 
		lp->counts--;
		deleted_elements++;
	}
	return deleted_elements;
}

//worst case Big O is O(n)
void maxAgeGap(SET *sp){
	assert(sp!=NULL);
	int first = 0, last = 13, age_gap;
	while(sp->flag[first]!=FILLED){	//finds the position of the first filled position in the array
		first++;
	}
	while(sp->flag[last]!=FILLED){	//finds the position of the last filled space in the array
		last--;
	}
	age_gap = last - first;
	printf("the max age gap is %d\n", age_gap);
	return;			
}
