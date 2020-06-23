#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pqueue.h"
#include "pack.h"
#include <ctype.h>
#define NODE struct node

int counts[257];
NODE *leaves[257];

//worst case big O is O(1)
static NODE *mknode(int data, NODE *left, NODE *right){
	NODE *np = malloc(sizeof(NODE));
	assert(np!=NULL);
	np->count = data;
	if(left!=NULL)
		left->parent = np;
	if(right!=NULL)
		right->parent = np;
	np->parent = NULL;
	return np;
}

//worst case big O is O(h)
static int depth(NODE *node){	//recursive function that returns the height/number of bits
	if(node->parent==0)
		return 0;
	return depth(node->parent)+1;
}

//worst case big O is O(1)
static int compare(NODE *left, NODE *right){	//compare function
	if(left->count<right->count)
		return -1;
	else if(left->count==right->count)
		return 0;
	else
		return 1;
}

//worst case big O is O(n)
int main(int argc, char*argv[0]){
	if(argc<2)
		return 0;
	int i, c;
	for(i=0;i<257;i++){	//initializes the global arrays
		counts[i]=0;
		leaves[i]=NULL;
	}
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp==NULL){		//if empty it returns
		printf("file is empty\n");
		return 0;	
	}
	while((c=getc(fp))!=EOF)	//adds every time the character is found in the text
		counts[c]++;	
	fclose(fp);
	PQ *pq=createQueue(compare);

	for(i=0;i<257;i++){
		if(counts[i]>0){
			leaves[i] = mknode(counts[i], NULL, NULL);
			addEntry(pq, leaves[i]);
		}
	}
	
	leaves[256] = mknode(counts[0], NULL, NULL);
	addEntry(pq, leaves[256]);

	while(numEntries(pq)>1){	//creates the parent nodes for the huffman tree
		NODE *node1 = removeEntry(pq);
		NODE *node2 = removeEntry(pq);
		int temp = node1->count + node2->count;
		addEntry(pq, mknode(temp, node1, node2));
	}
	
	for(i=0; i<257;i++){
		if(leaves[i]!=NULL){
			if(isprint(i)>0)	//if the integer is printable
				printf(" '%c': %d x %d bits = %d bits\n", i, counts[i], depth(leaves[i]), ((counts[i])*(depth(leaves[i]))));
			else
				printf(" %d: %d x %d bits = %d bits\n", i, counts[i], depth(leaves[i]), ((counts[i])*(depth(leaves[i]))));
		}
	}
	pack(argv[1], argv[2], leaves);
}
