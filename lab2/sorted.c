#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include <stdbool.h>


typedef struct set {   //initializes the set
        int length;
        int count;
        char **data;
} SET;

SET *sp;


SET *createSet(int maxElts){
        SET *sp = malloc(sizeof(SET));
        assert(sp!=NULL);
        sp->length = maxElts;
        sp->count = 0;
        sp->data = malloc(sizeof(char*)*maxElts);
        assert(sp->data!=NULL);
        return sp;
}

//the Big-O notation is O(logn)
static int binary_search(SET*sp, char*elt, bool *found){
	assert(sp!=NULL);
	int low=0, high=(sp->count)-1, mid;
	while(low<=high){
		mid=(low+high)/2;
		if(strcmp(elt, sp->data[mid])<0){		//if mid is too high it assigns a new value for high
			high = mid-1;
		}
		else if(strcmp(elt, sp->data[mid])>0){		//if mid is too low it assigns a new value for low
			low = mid+1;
		}
		else{
			*found=true;
			return mid;				//returns the index of where the element is found
		}
	}
	*found=false;
	return low;		
} 

//the Big-O notation is O(n)
void destroySet(SET*sp){
	assert(sp!=NULL);
	int i;
	for(i=0; i<sp->count; i++)
		free(sp->data[i]);				//frees the information pointed to by sp->data
	free(sp->data);
	free(sp);
	return;
}	

//the Big-O notation is O(1)
int numElements(SET*sp){
	assert(sp!=NULL);
	return sp->count;
}

//the Big-O notation is O(n)
void addElement(SET*sp, char*elt){
	assert(sp!=NULL);
	int i, idx;
	bool found;
	idx = binary_search(sp, elt, &found);
	if(sp->count==sp->length)		
		return;
	if(found==false){
		for(i=sp->count;i>idx;i--){
			sp->data[i] = sp->data[i-1];		//shifts the elements down
		}
		sp->data[idx]=strdup(elt);			//creates memory for the given index and copies the element
		(sp->count)++;
	}
	return;
}

//the Big-O notation is O(n)
void removeElement(SET*sp, char*elt){
	assert(sp->data!=NULL);
	int i, idx;
	bool found;
	idx = binary_search(sp, elt, &found);
	if(found==true){
		free(sp->data[idx]);				//frees the information pointed to by the index
		for(i=idx;i<(sp->count)-1;i++){
			sp->data[i] = sp->data[i+1]; 		//shifts the information up
		}
		(sp->count)--;
	}	
	return;
}

//the Big-O notation is O(1) not including the search and O(logn) including the search
char*findElement(SET*sp, char*elt){
	assert(sp!=NULL);
	bool found;
	int i;
	i = binary_search(sp, elt, &found);
	if(found==true)
		return sp->data[i];				//if found it returns the element
	return NULL;
}

//the Big-O notation is O(n)
char**getElements(SET*sp){
	assert(sp!=NULL);
	int i;
	char **copy;
	copy = malloc(sizeof(char *)*(sp->count));		//makes a copy of the array of pointers
	for(i=0; i<sp->count; i++)
		copy[i] = sp->data[i];				//copies the information pointed to to the copy
	return copy;
}

 
