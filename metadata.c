#include <unistd.h>
#include <lib.h>
#include "metadata.h"

void metadata_read(){
	register message *msgptr = malloc(sizeof(message));
	_syscall(VFS, 65, msgptr);
}