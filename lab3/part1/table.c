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
} SET;

SET *sp;

//the Big-O notation is O(1)
SET *createSet(int maxElts){
        SET *sp = malloc(sizeof(SET));
        assert(sp!=NULL);
        sp->length = maxElts;
        sp->count = 0;
        sp->data = malloc(sizeof(char*)*maxElts);
	sp->flag = malloc(sizeof(char)*maxElts);
        assert(sp->data!=NULL);
        return sp;
}

unsigned strhash(char *s){						//hash function
	unsigned hash =0;

	while (*s!='\0')
		hash = 31 * hash + *s ++;
	return hash;
} 

//the Big-O notation is O(n)
static int hash_search(SET*sp, char*elt, bool *found){
	assert(sp!=NULL);
	int i, index, position, deleted;
	position = strhash(elt) % (sp->length); 			//position is the value of hash function modulus length
	deleted = -1;
	for(i=0; i<sp->length; i++){					//for loop increments the postion each time
		index=(position+i) % sp->length;
		if(sp->flag[index]==EMPTY){
			*found=false;
			if(deleted!=-1)
				return deleted;				//if it's been deleted, it returns the position of the deleted spot
			else
				return index;				//if not deleted it returns position of empty spot
		}
		else if(sp->flag[index]==DELETED){
			if(deleted==-1)
				deleted=index;
		}
		else if(strcmp(elt, sp->data[index])==0){
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
	for(i=0; i<sp->count; i++){
		if(sp->flag[i]==FILLED){
			free(sp->data[i]);				//frees the information pointed to by sp->data
		}
	}
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
void addElement(SET*sp, char*elt){
	assert(sp!=NULL);
	int i, idx;
	bool found;
	idx = hash_search(sp, elt, &found);
	if(sp->count==sp->length)		
		return;
	if(found==false){
		sp->flag[idx] = FILLED;
		sp->data[idx] = strdup(elt);				//creates memory for the given index and copies the element
		(sp->count)++;
	}
	return;
}

//the Big-O notation is O(1) without the search function and O(n) with the search function
void removeElement(SET*sp, char*elt){
	assert(sp->data!=NULL);
	int i, idx;
	bool found;
	idx = hash_search(sp, elt, &found);
	if(found==true){
		free(sp->data[idx]);					//frees the information pointed to by the index
		sp->flag[idx] = DELETED;
		(sp->count)--;
	}	
	return;
}

//the Big-O notation is O(1) not including the search and O(n) including the search
char*findElement(SET*sp, char*elt){
	assert(sp!=NULL);
	bool found;
	int i;
	i = hash_search(sp, elt, &found);
	if(found==true)
		return sp->data[i];					//if found it returns the element
	return NULL;
}

//the Big-O notation is O(n)
char**getElements(SET*sp){
	assert(sp!=NULL);
	int i, j=0;
	char **copy;
	copy = malloc(sizeof(char *)*(sp->count));			//makes a copy of the array of pointers
	for(i=0; i<sp->length; i++)
		if(sp->flag[i]==FILLED){
			copy[j] = sp->data[i];				//copies the information pointed to to the copy
			j++;
		}
	return copy;
}

 
