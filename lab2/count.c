#include <stdio.h>
#include <stdlib.h>
# define MAX_WORD_LENGTH 30 //max word length is a global variable

int main(int argc,char *argv[]) //takes in number of elements in file and the textfile as an argument
{int counter=0, flag=0; 
 char character[MAX_WORD_LENGTH];
 FILE *fp;

 if(argc<2) //if not enough arguments it gives an error
	{printf("ERROR\n");
	 return 1;
	}

 fp=fopen(argv[1], "r");
 
 if(fp==NULL) //if file is empty it prints that
	{printf("Sorry there is no file\n");
	 return 1;
	} 

 while(fscanf(fp, "%s", character) == 1) //counts the number of strings
	counter++;
 printf("%d total words\n", counter);
 return 1;
 
}
