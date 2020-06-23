#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include <stdbool.h>
#define EMPTY 0
#define DELETED 1
#define FILLED 2

typedef struct set {   //initializes the set
        int length;
        int count;
        char **data;
	char *flag;
	int (*compare)();
	unsigned (*hash)();
} SET;

SET *sp;

//the Big-O notation is O(1)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
        SET *sp = malloc(sizeof(SET));
        assert(sp!=NULL);
        sp->length = maxElts;
        sp->count = 0;
        sp->data = malloc(sizeof(void*)*maxElts);
	sp->flag = malloc(sizeof(char)*maxElts);
	for(int i=0; i<maxElts; i++)
		sp->flag[i]=EMPTY;
        sp->compare = compare;
	sp->hash = hash;
	assert(sp->data!=NULL);
        return sp;
}
 

//the Big-O notation is O(n)
static int search(SET *sp, void *elt, bool *found){
	assert(sp!=NULL);
	int i, index, position, deleted;
	position = ((*sp->hash)(elt)) % (sp->length);
	deleted = -1;
	for(i=0; i<sp->length; i++){
		index=(position+i) % (sp->length);
		if(sp->flag[index]==EMPTY){
			*found=false;
			if(deleted!=-1)
				return deleted;				//if deleted, the position of the deleted spot is returned
			else
				return index;				//if not deleted, position of empty spot is returned
		}
		else if(sp->flag[index]==DELETED){
			if(deleted==-1)
				deleted=index;
		}
		else if((*sp->compare)(elt, sp->data[index])==0){
			*found=true;
			return index;
		}
			
	}
	*found=false;
	return deleted;
} 

//the Big-O notation is O(n)
void destroySet(SET*sp){
	assert(sp!=NULL);
	int i;
	free(sp->data);
	free(sp->flag);
	free(sp);
	return;
}	

//the Big-O notation is O(1)
int numElements(SET*sp){
	assert(sp!=NULL);
	return sp->count;
}

//the Big-O notation is O(1) not including the search function and O(n) including the search function
void addElement(SET*sp, void*elt){
	assert(sp!=NULL);
	int i, idx;
	bool found;
	idx = search(sp, elt, &found);
	if(sp->count==sp->length)		
		return;
	if(found==false){
		sp->flag[idx] = FILLED;
		sp->data[idx] = elt;					//pointer for data is now pointing to the new element
		(sp->count)++;
	}
	return;
}

//the Big-O notation is O(1) not including the search function and O(n) including the search function
void removeElement(SET*sp, void*elt){
	assert(sp->data!=NULL);
	int i, idx;
	bool found;
	idx = search(sp, elt, &found);
	if(found==true){
		sp->flag[idx] = DELETED;				//changes the flag to deleted
		(sp->count)--;
	}	
	return;
}

//the Big-O notation is O(1) not including the search and O(n) including the search
void*findElement(SET*sp, void*elt){
	assert(sp!=NULL);
	bool found;
	int i;
	i = search(sp, elt, &found);
	if(found==true)
		return sp->data[i];					//if found it returns the element
	return NULL;
}

//the Big-O notation is O(n)
void*getElements(SET*sp){
	assert(sp!=NULL);
	int i, j=0;
	char **copy;
	copy = malloc(sizeof(void *)*(sp->count));			//makes a copy of the array of pointers
	for(i=0; i<sp->length; i++)
		if(sp->flag[i]==FILLED){
			copy[j] = sp->data[i];				//copies the information pointed to to the copy
			j++;
		}
	return copy;
}

 
