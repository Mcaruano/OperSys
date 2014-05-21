#include <stdio.h>
#include "memory.h"

int main(int argc, char *argv[])
{
   int i;
   int *object;
   int value;

    /*Maybe use this main function to test*/
    printf("Beginning general malloc test.\n");

    object = (int*) malloc(10);

    if(object == NULL){
    	printf("malloc failed!\n");
    	return 0;
    }

    for(i = 0; i < 20; i ++){
       malloc(i * 100);
    }

    object[0] = 32;
    free(object);

    return 0;
}
