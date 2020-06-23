# ifndef LIST_H
# define LIST_H

typedef struct list LIST;

extern LIST *createList();

extern void destroyList(LIST *lp);

extern void searchAge(LIST *lp);

extern void insertion(SET *sp, int id, int age);

extern void addFirst(LIST *lp, int id, int age);

extern int removeRow(LIST *lp);

# endif
