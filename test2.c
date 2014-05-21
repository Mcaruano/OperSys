#include <stdio.h>
#include "memory.h"

int main(int argc, char *argv[])
{
	int i;
	char* ptrChar;
	
	printf("Test2: invalid address deallocate\n\n");
	for(i = 0; i < 10; i++)
	{
		ptrChar = (char*)malloc(sizeof(char) * i);
		free(ptrChar);
	}
	free(6000000);
    return 0;
}
