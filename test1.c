#include <stdio.h>
#include "memory.h"

int main(int argc, char *argv[])
{

	int i;
	char* ptrChar;
	
	printf("Test1: non­trivial allocation\n");
    for(i = 1; i < 10; i ++)
	{
       ptrChar = (char*)malloc(i * 10);
	   *ptrChar = (char)(i+40);
	   printf("ptrChar: %c\n", *ptrChar);
    }

    return 0;
}
