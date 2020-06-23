# ifndef SET_H
# define SET_H

typedef struct set SET;

extern SET *createDataSet(int maxElts);

extern void destroyDataSet(SET *sp);

extern void findAge(SET *sp, int age);

extern void insertion(SET *sp, int id, int age);

extern void deletion(SET *sp, int age);

extern void maxAgeGap(SET *sp);

#endif
