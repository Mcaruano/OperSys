/* This file is the counterpart of "read.c".  It contains the code for writing
 * insofar as this is not contained in read_write().
 *
 * The entry points into this file are
 *   do_write:     call read_write to perform the WRITE system call
 */

#include <stdio.h>

#include "fs.h"
#include "file.h"
#include "fproc.h"


/*===========================================================================*
 *				do_write				     *
 *===========================================================================*/
PUBLIC int do_write()
{
/* Perform the write(fd, buffer, nbytes) system call. */
  return(read_write(WRITING));
}

/*===========================================================================*
 *				do_write				     *
 *===========================================================================*/
PUBLIC int do_mwrite()
{
	printf("I'm in do_write()\n");
/* Perform the write(fd, buffer, nbytes) system call. */
  return(mread_write(WRITING));
}
