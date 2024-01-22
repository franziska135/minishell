#include "minishell.h"

static int	child_proccess(t_compound *cmds, int *fd, int i)
{
	char	*path;

	if (cmds->scmd[i].in_fd != -1 && cmds->scmd[i].out_fd != -1)
	{
		// if (cmds->scmd[i].out_fd != 0)
		// 	dup2(fd[1], cmds->scmd->out_fd);
		// else
		// 	dup2(fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
 		path = path_finder(cmds, i);
		if (!path)
		{
			struct_free(*cmds);
			exit (EXIT_FAILURE);
		}
		execve(path, cmds->scmd[i].cmd, cmds->envp);
	}
	exit (EXIT_FAILURE);
}


static int	piping(t_compound *cmds)
{
	int	fd[2];
	int	i;
	int	pid;

	i = 0;

	while (i < cmds->nbr_scmd)
	{
		if (pipe(fd) == -1)
			return (0);
		pid = fork();
		if (pid == 0)
			child_proccess(cmds, fd, i);
		close (fd[1]);
		// if (cmds->scmd[i].in_fd != 0)
		// 	dup2(fd[0], cmds->scmd[i].in_fd);
		// else
		// 	dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		i++;
	}
	if (waitpid(pid, NULL, 0) == -1)
		return(0);
	close (fd[0]);
	close (fd[1]);
	return (1);
}

int	piping_root(t_compound *cmds)
{
	sleep(1);
	return (piping(cmds));
}