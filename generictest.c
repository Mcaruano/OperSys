#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "metadata.h"

int main(int argc, char *argv[])
{

	char buffer[128];
	int fd_in, fd_out;
	ssize_t bytes;

	fd_in = open("testread", O_RDONLY);
	if(fd_in == -1){
		printf("failed to open file.\n");
		return;
	}

	bytes = metadata_read(fd_in, buffer, sizeof(buffer));
	close(fd_in);

	printf("\nSuccessfully read %d bytes.\n", bytes);

	fd_out = open("testwrite", O_RDWR | O_CREAT );
	printf("\nThese are the permissions for testwrite\n");
    fflush(stdout);

    metadata_write(fd_out, buffer, bytes);
    close(fd_out);


	
    return 0;
}
