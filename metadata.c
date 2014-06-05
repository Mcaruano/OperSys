#include <unistd.h>
#include <lib.h>
#include "metadata.h"

void metadata_read(){
	register message *msgptr = (message*)malloc(sizeof(message));
	_syscall(VFS_PROC_NR, 65, msgptr);
}
