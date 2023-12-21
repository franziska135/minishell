#include "../minishell.h"

// for closedir valgrind --leak-check=full

int main()
{
	struct dirent	*dp;
	DIR				*dir;
	char			str[100];
	int				fd;


	dir = opendir("../");
	if (dir == NULL)
	{
		perror(NULL);
		exit(1);
	}
	dp = readdir(dir);
	while (dp != NULL)
	{
		printf("\nNEXT ITEMS:\n");
		printf("name: %s\n", dp->d_name);
		printf("ino: %ld\n", dp->d_ino);
		printf("off: %ld\n", dp->d_off);
		printf("reclen: %d\n", dp->d_reclen);
		printf("type: %d\n", dp->d_type);
		dp = readdir(dir);
	}
	closedir (dir);
	
					// POSSIBLE USECASE:
	dir = opendir("../");
	if (dir == NULL)
	{
		perror(NULL);
		exit(1);
	}
	dp = readdir(dir);
	while (dp != NULL)
	{
		if (strncmp(dp->d_name, "Makefile", 9) == 0)
		{
			chdir("../");
			fd = open(dp->d_name, O_RDONLY);
			read(fd, str, 100);
			str[100] = '\0';
			printf ("\n\n%s\n", str);
			close(fd);
		}
		dp = readdir(dir);
	}
	closedir(dir);
}