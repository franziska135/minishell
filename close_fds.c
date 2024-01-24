#include "minishell.h"

void	close_fds(t_compound *cmds, int *fd)
{
	int	i;

	i = 0;
	while (i < cmds->nbr_scmd)
	{
		if (cmds->scmd[i].in_fd > 2)
			close (cmds->scmd[i].in_fd);
		if (cmds->scmd[i].out_fd > 2)
			close (cmds->scmd[i].out_fd);
		i++;
	}
	if (fd)
	{
		close (fd[0]);
		close (fd[1]);
	}
}