#include <stdio.h>
#include "memory.h"

int main(int argc, char *argv[])
{
   int i;

    /*Maybe use this main function to test*/
    printf("Beginning malloc test.\n");

    int *object = (int*) malloc(10);

    if(object == NULL){
    	printf("malloc failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    	return 0;
    }

    printf("malloc succeeded!?!?!?!?\n");
    object[0] = 32;
    int value = object[0];
    printf("object[0] = %d\n", value);

    for(i = 0; i < 20; i ++){
       malloc(i * 100);
    }

    slug_memstats();

    return 0;
}
