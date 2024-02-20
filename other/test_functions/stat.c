#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"

//COMPILE:	cc stat.c ../libft/*.c
int main()
{
	char	buf[100];
	char	*path;
	struct stat statbuf;

	getcwd(buf, 100);
	path = ft_strjoin(buf, "/stat.c");
	// printf ("%s\n", path);
	if (stat(path, &statbuf) == -1)
		perror(NULL);
	printf ("dev: %ld\n", statbuf.st_dev);				/*This field describes the device on which this file resides.  (The major(3) and minor(3)
              												macros may be useful to decompose the device ID in this field.)*/
	printf ("ino: %ld\n", statbuf.st_ino);				//This field contains the file's inode number.
	printf ("mode: %u\n", statbuf.st_mode);				//This field contains the file type and mode.  See inode(7) for further information.
	printf ("nlink: %ld\n", statbuf.st_nlink);			//This field contains the number of hard links to the file.
	printf ("uid: %u\n", statbuf.st_uid);				//This field contains the user ID of the owner of the file.
	printf ("gid: %u\n", statbuf.st_gid);				//This field contains the ID of the group owner of the file.
	printf ("rdev: %ld\n", statbuf.st_rdev);			//This field describes the device that this file (inode) represents.
	printf ("size: %ld\n", statbuf.st_size);			/*This  field  gives the size of the file (if it is a regular file or a symbolic link) in
															bytes.  The size of a symbolic link is the length of the pathname it contains,  without
															a terminating null byte.*/
	printf ("blksize: %ld\n", statbuf.st_blksize);		//This field gives the "preferred" block size for efficient filesystem I/O.
	printf ("blocks: %ld\n", statbuf.st_blocks);		/*This  field  indicates  the  number of blocks allocated to the file, in 512-byte units.
              												(This may be smaller than st_size/512 when the file has holes.)*/
	printf ("atime: %ld\n", statbuf.st_atime);			//This is the time of the last access of file data.
	printf ("mtime: %ld\n", statbuf.st_mtime);			//This is the time of last modification of file data.
	printf ("ctime: %ld\n", statbuf.st_ctime);			//This is the file's last status change timestamp (time of last change to the inode)


	if (fstat(2, &statbuf) == -1)
		perror(NULL);
	// printf ("%ld\n", statbuf.st_size);

	

}
