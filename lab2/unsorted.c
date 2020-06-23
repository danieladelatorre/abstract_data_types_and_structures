/* Daniela De La Torre
   COEN 12
   April 11 2019
   Abstract Data Structures
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"

typedef struct set {
	int length;
	int count;
	char **data;
} SET;

SET *sp;

//this function creates the set
SET *createSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data!=NULL);
	return sp;
}

//the Big-O notation is O(n)
static int search(SET *sp, char *elt){
         int idx;
         assert(sp->data!=NULL);
         for(idx=0; idx<sp->count; idx++)
                 if(strcmp(sp->data[idx], elt)==0)	//compares the strings and returns the index if found
                         return idx;
         return -1;
 }

//the Big-O notation is O(n)
void destroySet(SET *sp) {
	int i;
	assert(sp!=NULL);
	for(i=0; i<sp->count; i++)
		free(sp->data[i]);			//frees the information pointed to by data
	free(sp->data);					//frees the array of pointers
	free(sp);
	return;
}

//the Big-O notation is O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return(sp->count);
}

//the Big-O notation is O(1) not including the search and O(n) with the search
void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int i;
	if(sp->count==sp->length)
		return;
	i=search(sp, elt);
	if(i==-1){
		sp->data[sp->count]=strdup(elt);	//creates a memory space and assigns the element to the last index
		(sp->count)++;
	}
	return;
}

//the Big-O notation is O(1) not including the search and O(n) with the search
void removeElement(SET*sp, char*elt){
	int i;
	assert(sp->data!=NULL);
	i = search(sp, elt);
	if(i!=-1){
		free(sp->data[i]);
		(sp->count)--;
		sp->data[i] = sp->data[sp->count];	//pointer to the removed element is now pointing at the last element
		}
	return;
}

//the Big-O notation is O(1) not including the search and O(n) with the search
char *findElement(SET*sp, char*elt){
	int i = search(sp, elt);
	if(i!=-1)
		return sp->data[i];			//if found, it will return the element
	return NULL;
}

//the Big-O notation is O(n)
char **getElements(SET *sp){
	assert(sp!=NULL);
	int i;
	char **copy;
	copy = malloc(sizeof(char*)*(sp->count));	//creates a copy of the array of pointers
	for(i=0; i<sp->count; i++)			//assigns the values of sp->data to copy (copies the information)
		copy[i] = sp->data[i];
	return(copy);
	}	
