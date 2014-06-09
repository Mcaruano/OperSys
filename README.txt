We have not used any grace days prior to this project, so we are using them all for this submission.
We are turning in a half-completed Project 4.

In order to make grading this significantly easier for you, here is what we changed:
- metadata.c implements user-space functions metadata_read() and metadata_write
- metadata_read() calls do_mread syscall, located at index 65 in vfs/table.c
- do_mread() is implemented in vfs/read.c
- metadata_write() calls do_mwrite syscall, located at index 66 in vfs/table.c
- do_mwrite is implemented in vfs/write.c
- BOTH do_mread and do_mwrite call mread_write() and pass in a flag indicating which action to do
- mread_write is implemented in read.c

- To go from VFS to MFS, we created a function req_mreadwrite in vfs/request.c
- mread_write calls req_mreadwrite.
- req_mreadwrite then invokes fs_readwrite in mfs/read.c, where we have custom handling for metadata actions
- The way we tell fs_readwrite if it is a metadata action is through setting m9_s1 to -1 in the message in req_mreadwrite

- fs_readwrite gets ahold of the i_node for the the file using the REQ_INODE_NR flag within the message struct
- the block for the zone 9 of the block zone pointers on the inode struct is allocated (if not already), to be used to store the user metadata.
- The functionality of actually writing to and reading from the block is not implemented.

- generictest.c is a very simple program that opens a plain text file testread, with read only permissions
- reads the data into a buffer using our metadata_read() call, printing out with a confirmation, then closing the file
- opens a new, empty file "testwrite", with writing and creating permissions
- writes the data from the previous buffer into the file using our metadata_write() call, then closes the file.
- These two operations will cause a print statement to execute within the fs_readwrite() functions of MFS
- This indicates that we had gotten far enough to route our own system calls from user space to MFS, with the ability to distinguish between normal and meta calls within the fs_readwrite() function.

'make', 'make all' or 'make generictest' will create this generictest executable. Run the executable via ./generictest, with no arguments.
