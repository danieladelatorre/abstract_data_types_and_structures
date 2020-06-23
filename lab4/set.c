#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"

struct set {
	int count;
	int length;
	LIST **lists;
	int (*compare)();
	unsigned (*hash)();
};

//Big O run time is O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	int i;
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts/20;
	sp->compare = (*compare);
	sp->hash = (*hash);
	sp->lists = malloc(sizeof(LIST*)*sp->length);	//allocates memory for the list
	for(i=0; i<sp->length; i++)
		sp->lists[i] = createList(compare);
	return sp;
}

//worst case Big O is O(n) not including the destroyList function and O(n^2) including the function
void destroySet(SET *sp){
	assert(sp!=NULL);
	int i;
	for(i=0; i<sp->length; i++){
		destroyList(sp->lists[i]);	//traverses and frees all nodes in the list
	}
	free(sp->lists);
	free(sp);
	return;
}

//worst case Big O is O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;	//returns the number of elements
}

//worst case Big O is O(1) without the findItem funciton and O(n) including the time for the findItem function
void addElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);
	int position;
	position = (*sp->hash)(elt) % (sp->length);
	if(findItem(sp->lists[position], elt)==NULL){	//if it's NULL then the element was not found and we can add it
		addLast(sp->lists[position], elt);	
		sp->count++;	
	}
	return;
}

//worst case Big O is O(1) without the findItem funciton and O(n) including the time for the findItem function
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);
	int position;
	position = (*sp->hash)(elt) % (sp->length);
	if(findItem(sp->lists[position], elt)!=NULL){	//if it's not NULL then the element was found and we can then free it
		removeItem(sp->lists[position], elt);			
		sp->count--;
	}
	return;	
}

//worst case Big O is O(1) not including the findItem function and O(n) including the run time for the function
void *findElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);
	int position;
	position = (*sp->hash)(elt)%(sp->length);
	return findItem(sp->lists[position], elt);
}

//worst case Big O is O(n^2)
void *getElements(SET *sp){
	assert(sp!=NULL);
	void **copy;
	copy = malloc(sizeof(void*)*sp->count);
	assert(copy!=NULL);
	int i, j=0;
	for(i=0; i<sp->length; i++){
		memcpy(copy+j, getItems(sp->lists[i]), sizeof(void*)*numItems(sp->lists[i]));	//copies the data in each linked list to copy
		j+=numItems(sp->lists[i]);
	}
	return copy;
}
