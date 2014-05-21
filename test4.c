#include <stdio.h>
#include "memory.h"

int main(int argc, char *argv[])
{
	int i;
	char* ptrChar;
	char* ptrTemp;
	
	printf("Test4: pointer inside the region\n\n");
	for(i = 0; i < 10; i++)
	{
		ptrChar = (char*)malloc(sizeof(char) * i);
		free(ptrChar);
	}
	ptrTemp = (char*)malloc(100);
	ptrTemp+= 1;
	free(ptrTemp);
   return 0;
}
