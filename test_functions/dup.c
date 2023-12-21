#include "../minishell.h"

int main()
{
	int fd = dup(1);
	// printf ("%d\n", fd);
	write (3, "Hello world!\n", 13);
	close (1);
	write (3, "Hello world!\n", 13);
}