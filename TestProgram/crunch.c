#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    unsigned i, j;

    for(j = 1; j < 7; j++){
        for(i = 1; i < 4000000000; i++) {}
    }

	return 0;
}