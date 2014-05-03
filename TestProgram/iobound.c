#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    unsigned i, j;
    FILE* test_file1;

    test_file1 = fopen("iobound.txt", "w");

    /* Populate the files */
    for(i = 0;; i++){
        for(j = 0; j < 4000000; j++){ 
            fprintf(test_file1, "%u \n", j);
        }

        rewind(test_file1);
        printf("%d\n", i);
    }

    fclose(test_file1);

    return 0;
}
