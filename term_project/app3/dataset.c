#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

typedef struct node{
	int age;
	int id;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct list{
	int length;
	int count;
	int min_age;
	int max_age;
	NODE *head;;
}LIST;
	
LIST *lp;

//worst case Big O is O(1)
LIST *createList(int maxElts){
	LIST *lp = malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->head = malloc(sizeof(NODE));
	assert(lp->head!=NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	lp->count = 0;
	lp->length = maxElts;
	lp->min_age = 0;
	lp->max_age = 0;
	return lp;
	
}

//worst case Big O is O(n)
void destroyDataSet(LIST *lp){
	assert(lp!=NULL);
	NODE *pDel, *pNext;
	pDel = lp->head;
	do{
		pNext = pDel->next;
		free(pDel);
		pDel = pNext;
	}while(pDel!=lp->head);
	free(lp);
	return;
}

//this function inserts the new element to the beginning of the list
//worst case Big O is O(1)
void insertion(LIST *lp, int age, int id){
	assert(lp!=NULL);
	NODE *temp;
	if(lp->count == lp->length){
		printf("sorry no more room\n");
		return;
	}
	temp = malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->age = age;
	temp->id = id;
	temp->next = lp->head->next;
	temp->prev = lp->head;
	lp->head->next->prev = temp;
	lp->head->next = temp;
	lp->count++;
	return;
}

//this function prints the elements with the given age if found
//worst case Big O is O(n)
void searchAge(LIST *lp, int age){
	assert(lp!=NULL);
	int found_items = 0;
	NODE *plocation;
	plocation = lp->head->next;
	while(plocation!=lp->head){
		if(plocation->age == age){
			printf("age = %d, id = %d\n", plocation->age, plocation->id);	//prints the students information if age matches
			found_items++;
			plocation = plocation->next;
		}
		else plocation = plocation->next;		
	}
	if(found_items!=0){	//if ages match then it will print found
		printf("found\n");
		return;
	}
	printf("no results found");
	return;
}

//this function searches for the given student id and returns the pointer to it if found
//worst case Big O is O(n)
void *searchId(LIST *lp, int id){
	assert(lp!=NULL);
	int flag;
	NODE *plocation = lp->head->next;
	while(plocation!=lp->head){
		if(plocation->id == id){	//if found, it returns the pointer to the node
			printf("found\n");
			flag = 1;
			return plocation;
		}
		plocation = plocation->next;
	}
	printf("there is no id with that number\n");
	return NULL;
}

//this function deletes the student record from the list
//worst case Big O is O(1) not including the searchId function and O(n) including the function
void deletion(LIST *lp, int id){
	assert(lp!=NULL);
	NODE *pDel = searchId(lp, id);
	if(pDel==NULL){
		printf("there are no students with that id\n");
		return;
	}
	else{	//if the id was found in the previous function, it deletes the student with that record
		pDel->prev->next = pDel->next;
		pDel->next->prev = pDel->prev;
		lp->count--;
		free(pDel);	
		printf("successfully deleted\n");
		return;
	}
	
}

//this function updates the values of the min and max variables in the set so its faster to call in maxAgeGap function
//worst case Big O is O(n)
void min_max_Age(LIST *lp){
	assert(lp!=NULL);
	assert(lp->count>=2);
	NODE *plocation = lp->head->next;
	lp->min_age = plocation->age;
	lp->max_age = plocation->age;
	while(plocation->next!=lp->head){
		if(plocation->next->age < lp->min_age)
			lp->min_age = plocation->next->age;	//if the locations age is smaller than variable, it is the new min
		else if(plocation->next->age > lp->max_age)	//if the locations age is larger than variable, it is the new max
			lp->max_age = plocation->next->age;	
		plocation = plocation->next;
	}	
	return;
}

//worst case Big O is O(1) not including the min_max_Age function and O(n) including the min_max_Age function
void maxAgeGap(LIST *lp){
	assert(lp!=NULL);
	assert(lp->count>=2);	//must make sure there are at least 2 items in the list to calculate the age gap
	min_max_Age(lp);
	int gap = lp->max_age - lp->min_age;
	printf("max age gap is %d\n", gap);
	return;
}
