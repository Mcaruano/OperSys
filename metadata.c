#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lib.h>
#include <fcntl.h>
#include "metadata.h"

ssize_t metadata_read(int fd, char *buffer, unsigned bytes){

	register message *m;

	/*
	fd = open("testread", O_RDONLY);
	if(fd == -1){
		printf("failed to open file.\n");
		return;
	}

	bytes = read(fd, buffer, sizeof(buffer)); */



	m = (message*)malloc(sizeof(message));
	m->m1_i1 = fd;
  	m->m1_i2 = bytes;
  	m->m1_p1 = buffer;
	return(_syscall(VFS_PROC_NR, 65, m));

	/* close(fd);

	printf("successfully read %d bytes.\n", bytes); */
}

ssize_t metadata_write(int fd, char *buffer, unsigned bytes){

	register message *m;

	/*
	fd = open("testread", O_RDONLY);
	if(fd == -1){
		printf("failed to open file.\n");
		return;
	}

	bytes = read(fd, buffer, sizeof(buffer)); */



	m = (message*)malloc(sizeof(message));
	m->m1_i1 = fd;
  	m->m1_i2 = bytes;
  	m->m1_p1 = buffer;
	return(_syscall(VFS_PROC_NR, 66, m));

	/* close(fd); 

	printf("successfully read %d bytes.\n", bytes); */
}
