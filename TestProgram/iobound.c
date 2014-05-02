#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    unsigned i;
    FILE* test_file;
    int input;

    for(i = 0;; i++){

        /* Read huge file */
        test_file = fopen("bigread.txt", "r");

        do {
            input = getc(test_file);
        } while (input != EOF);
        
        fclose(test_file);

        printf("%d\n", i);
    }

    return 0;
}