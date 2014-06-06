#include "fs.h"
#include <assert.h>
#include <stdio.h>
#include <minix/vfsif.h>
#include "inode.h"


/*===========================================================================*
 *				fs_sync					     *
 *===========================================================================*/
PUBLIC int fs_sync()
{
/* Perform the sync() system call.  Flush all the tables. 
 * The order in which the various tables are flushed is critical.  The
 * blocks must be flushed last, since rw_inode() leaves its results in
 * the block cache.
 */
  struct inode *rip;
  struct buf *bp;

  assert(nr_bufs > 0);
  assert(buf);

  /* Write all the dirty inodes to the disk. */
  for(rip = &inode[0]; rip < &inode[NR_INODES]; rip++)
	  if(rip->i_count > 0 && rip->i_dirt == DIRTY) rw_inode(rip, WRITING);

  /* Write all the dirty blocks to the disk, one drive at a time. */
  for(bp = &buf[0]; bp < &buf[nr_bufs]; bp++)
	  if(bp->b_dev != NO_DEV && bp->b_dirt == DIRTY) 
		  flushall(bp->b_dev);

  return(OK);		/* sync() can't fail */
}


/*===========================================================================*
 *				fs_flush				     *
 *===========================================================================*/
PUBLIC int fs_flush()
{
/* Flush the blocks of a device from the cache after writing any dirty blocks
 * to disk.
 */
  dev_t dev = (dev_t) fs_m_in.REQ_DEV;
  if(dev == fs_dev) return(EBUSY);
 
  flushall(dev);
  invalidate(dev);
  
  return(OK);
}

/*===========================================================================*
 *        fs_testread             *
 *===========================================================================*/
PUBLIC int fs_testread(void)
{
  int r, rw_flag, block_spec;
  int regular;
  cp_grant_id_t gid;
  off_t position, f_size, bytes_left;
  unsigned int off, cum_io, block_size, chunk;
  mode_t mode_word;
  int completed;
  struct inode *rip;
  size_t nrbytes;

  printf("inside the mfs\n");
  
  r = OK;
  
  /* Find the inode referred */
  if ((rip = find_inode(fs_dev, (ino_t) fs_m_in.REQ_INODE_NR)) == NULL)
  return(EINVAL);

  mode_word = rip->i_mode & I_TYPE;
  regular = (mode_word == I_REGULAR || mode_word == I_NAMED_PIPE);
  block_spec = (mode_word == I_BLOCK_SPECIAL ? 1 : 0);
  
  /* Determine blocksize */
  if (block_spec) {
  block_size = get_block_size( (dev_t) rip->i_zone[0]);
  f_size = MAX_FILE_POS;
  } else {
    block_size = rip->i_sp->s_block_size;
    f_size = rip->i_size;
  }

  /* Get the values from the request message */ 
  rw_flag = (fs_m_in.m_type == REQ_READ ? READING : WRITING);
  gid = (cp_grant_id_t) fs_m_in.REQ_GRANT;
  position = (off_t) fs_m_in.REQ_SEEK_POS_LO;
  nrbytes = (size_t) fs_m_in.REQ_NBYTES;
  
  rdwt_err = OK;    /* set to EIO if disk error occurs */

  if (rw_flag == WRITING && !block_spec) {
    /* Check in advance to see if file will grow too big. */
    if (position > (off_t) (rip->i_sp->s_max_size - nrbytes))
      return(EFBIG);

    /* Clear the zone containing present EOF if hole about
     * to be created.  This is necessary because all unwritten
     * blocks prior to the EOF must read as zeros.
     */
    if(position > f_size) clear_zone(rip, f_size, 0);
  }
        
  cum_io = 0;
  /* Split the transfer into chunks that don't span two blocks. */
  while (nrbytes > 0) {
    off = ((unsigned int) position) % block_size; /* offset in blk*/
    chunk = min(nrbytes, block_size - off);

    if (rw_flag == READING) {
      bytes_left = f_size - position;
      if (position >= f_size) break;  /* we are beyond EOF */
      if (chunk > (unsigned int) bytes_left) chunk = bytes_left;
    }
    
    /* Read or write 'chunk' bytes. */
    r = rw_chunk(rip, cvul64((unsigned long) position), off, chunk,
             nrbytes, rw_flag, gid, cum_io, block_size, &completed);

    if (r != OK) break; /* EOF reached */
    if (rdwt_err < 0) break;

    /* Update counters and pointers. */
    nrbytes -= chunk; /* bytes yet to be read */
    cum_io += chunk;  /* bytes read so far */
    position += (off_t) chunk;  /* position within the file */
  }

  fs_m_out.RES_SEEK_POS_LO = position; /* It might change later and the VFS
             has to know this value */
  
  /* On write, update file size and access time. */
  if (rw_flag == WRITING) {
    if (regular || mode_word == I_DIRECTORY) {
      if (position > f_size) rip->i_size = position;
    }
  } 

  /* Check to see if read-ahead is called for, and if so, set it up. */
  if(rw_flag == READING && rip->i_seek == NO_SEEK &&
     (unsigned int) position % block_size == 0 &&
     (regular || mode_word == I_DIRECTORY)) {
    rdahed_inode = rip;
    rdahedpos = position;
  } 

  rip->i_seek = NO_SEEK;

  if (rdwt_err != OK) r = rdwt_err; /* check for disk error */
  if (rdwt_err == END_OF_FILE) r = OK;

  if (r == OK) {
    if (rw_flag == READING) rip->i_update |= ATIME;
    if (rw_flag == WRITING) rip->i_update |= CTIME | MTIME;
    rip->i_dirt = DIRTY;    /* inode is thus now dirty */
  }
  
  fs_m_out.RES_NBYTES = cum_io;
  
  return(r);
}