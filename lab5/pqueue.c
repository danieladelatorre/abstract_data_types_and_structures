#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

typedef struct pqueue{
	int count;
	int length;
	void **data;
	int (*compare)();
}PQ;

PQ *pq;

//worst case big O is O(1)
PQ*createQueue(int (*compare)()){
	PQ *pq = malloc(sizeof(PQ));
	assert(pq!=NULL);
	pq->compare = compare;
	pq->count = 0;
	pq->length = 10;
	pq->data = malloc(sizeof(void*)*(pq->length));
	assert(pq->data!=NULL);
	return pq;
}

//worst case big O is O(n)
void destroyQueue(PQ *pq){
	assert(pq!=NULL);
	int i;
	for(i=0; i<pq->count; i++){
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);
	return;
}

//worst case big O is O(1)
int numEntries(PQ *pq){
	assert(pq!=NULL);
	return pq->count;
}

//worst case big O is O(logn)
void addEntry(PQ*pq, void*entry){
	assert(pq!=NULL && entry!=NULL);
	int i, parent;
	if(pq->count == pq->length){
		pq->length *= 2;
		pq->data = (void *)realloc(pq->data, sizeof(void*)*(pq->length));	//doubles the size of the array when its full
	}
	pq->data[pq->count] = entry;
	i = pq->count;
	parent = (i-1)/2;
	while(i!=0 && (*pq->compare)(pq->data[i],pq->data[parent])<0){
		pq->data[i] = pq->data[parent];
		pq->data[parent] = entry;
		i = parent; 
		parent = ((i-1)/2);
	}
	pq->count++;
	return;
}

//worst case big O is O(logn)
void reheap(PQ *pq, int i){
	int right, left, min;
	void *temp;
	min = i;
	right =  (2*i)+2;
	left = (2*i)+1;
	if(left<pq->count && (*pq->compare)(pq->data[left], pq->data[min])<0)     //if left is smaller, left is min
		min = left;
	if(right<pq->count && (*pq->compare)(pq->data[right], pq->data[left])<0)   //if right is smaller, right is min
		min = right;
	if(min!=i){     //if parent is not min must swap values
		temp = pq->data[min];
		pq->data[min] = pq->data[i];
		pq->data[i] = temp;
		reheap(pq, min);
	}
	return;
}

//worst case big O is O(logn) including the reheap function
void*removeEntry(PQ*pq){
	assert(pq!=NULL);
	void *smallest;
	smallest = pq->data[0];
	pq->data[0] = pq->data[(pq->count)-1];
	pq->data[(pq->count)-1] = NULL;	
	pq->count--;
	reheap(pq, 0);	//calls the reheap function to swap the values if needed
	return smallest;
}

