#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"

int main(){
	int i, maxElts = 3000, age, id = 0, random_id;
	LIST *lp = createList(maxElts);
	srand(time(NULL));
	for(i=0; i<1000; i++){
		age = (rand()%13)+18;
		id += (rand()%2)+1;
		insertion(lp, age, id);
	}
	random_id = (rand()%2001)+1;
	searchId(lp, random_id);
	deletion(lp, random_id);
	maxAgeGap(lp);
	destroyDataSet(lp);		
	return 0;
}
	
