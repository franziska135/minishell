#include "minishell.h"

static int	child_proccess(t_compound *cmds, int *fd, int i, int initial_stdin)
{
	char	*path;

	close (initial_stdin);
	if (cmds->scmd[i].in_fd != -1 && cmds->scmd[i].out_fd != -1)
	{
		if (cmds->scmd[i].out_fd != 0)
			dup2(cmds->scmd[i].out_fd, STDOUT_FILENO);
		else if (i != cmds->nbr_scmd - 1)
			dup2(fd[1], STDOUT_FILENO);
		close_fds(cmds, fd);
 		path = path_finder(cmds, i);
		if (!path)
		{
			struct_free(*cmds);
			exit (EXIT_FAILURE);
		}
		execve(path, cmds->scmd[i].cmd, cmds->envp);
	}
	perror("child");
	exit (EXIT_FAILURE);
}


static int	piping(t_compound *cmds)
{
	int	fd[2];
	int	i;
	int	pid;
	int	initial_stdin;

	initial_stdin = dup(STDIN_FILENO);
	i = 0;
	while (i < cmds->nbr_scmd)
	{
		if (pipe(fd) == -1)
			return (0);
		if (cmds->scmd[i].in_fd != 0)
		{
			dup2(cmds->scmd[i].in_fd, STDIN_FILENO);
			close (cmds->scmd[i].in_fd);
		}
		pid = fork();
		if (pid == 0)
			child_proccess(cmds, fd, i, initial_stdin);
		close (fd[1]);
		if (i < (cmds->nbr_scmd - 1) && cmds->scmd[i + 1].in_fd == 0)
			dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		if (cmds->scmd[i].out_fd != 0)
			close (cmds->scmd[i].out_fd);
		i++;
	}
	if (waitpid(pid, NULL, 0) == -1)
		return(0);
	dup2(initial_stdin, STDIN_FILENO);
	close (initial_stdin);
	close (fd[0]);
	close (fd[1]);
	return (1);
}

int	piping_root(t_compound *cmds)
{
	if (!piping(cmds))
	{
		dup2(0, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
		return (0);
	}

	return (1);

}