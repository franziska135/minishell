#include "minishell.h"

void	print_dpointer(char **str)
{
	int	i = 0;

	while (str[i])
	{
		printf("%s, ", str[i]);
		i++;
	}
	printf ("\n");
}

void	print_struct(t_compound ccmd)
{
	int		i = 0;

	while (i < ccmd.nbr_scmd)
	{
		printf("\nPipe %d:\n", i + 1);
		printf("commands: ");
		print_dpointer(ccmd.scmd[i].cmd);

		printf ("in_fd: %d\t\tout_fd:%d\n", ccmd.scmd[i].in_fd, ccmd.scmd[i].out_fd);
		i++;
	}
}