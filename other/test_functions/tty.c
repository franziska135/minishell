#include "../minishell.h"

int main()
{
	int	fd = open("../minishell", O_RDONLY);
	printf("\nis std a tty: %d\n", isatty(0));
	printf("is null a tty: %d\n", isatty(5));
	printf("is fd a tty: %d\n\n", isatty(fd));

	printf("name std: %s\n", ttyname(0));
	printf("name null: %s\n", ttyname(5));
	printf("name fd: %s\n\n", ttyname(fd));

	printf("is slot:%d\n", ttyslot());					// cant understand fully


}