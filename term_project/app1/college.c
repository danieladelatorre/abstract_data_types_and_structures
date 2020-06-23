#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "set.h"
#include "list.h"

//worst case Big O is O(n)
int main(){
	int i, age, id=0, maxElts = 3000, random_id;
	SET *sp = createDataSet(maxElts);
	LIST *lp = createList();
	srand((int)time(NULL));
	for(i=0;i<1000;i++){
		age = (rand()%13)+18;
		id += (rand()%2)+1;
		insertion(sp, id, age);
	}
	random_id = (rand()%2001)+1;
	findAge(sp, age);
	deletion(sp, age);
	maxAgeGap(sp);
	destroyDataSet(sp);
	return 0;
}	

