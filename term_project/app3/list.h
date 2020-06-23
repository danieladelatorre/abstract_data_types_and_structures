# ifndef LIST_H
# define LIST_H

typedef struct list LIST;

extern LIST *createList(int maxElts);

extern void destroyDataSet(LIST *lp);

extern void insertion(LIST *lp, int age, int id);

extern void searchAge(LIST *lp, int age);

extern void *searchId(LIST *lp, int id);

extern void deletion(LIST *lp, int id);

extern void min_max_Age(LIST *lp);

extern void maxAgeGap(LIST *lp);

# endif
