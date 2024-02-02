#include "minishell.h"

static int	is_built_in(char *str)
{
	if (!str)
		return (FALSE);
	if (!ft_strncmp(str, "cd", 3))
		return (TRUE);
	else if (!ft_strncmp(str, "export", 7))
		return (TRUE);
	else if (!ft_strncmp(str, "unset", 6))
		return (TRUE);
	else if (!ft_strncmp(str, "env", 4))
		return (TRUE);
	else if (!ft_strncmp(str, "exit", 5))
		return (TRUE);
	else if (!ft_strncmp(str, "echo", 5))
		return (TRUE);
	return (FALSE);
}

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
		if (is_built_in(cmds->scmd[i].cmd[0]))
		{
			if_builtin_execute(cmds, &cmds->scmd[i]);
			cleanup_envp_ll(cmds->env_ll);
			struct_free(*cmds);
			exit (EXIT_SUCCESS);
		}
 		path = path_finder(cmds, i);
		if (!path)
		{
			cleanup_envp_ll(cmds->env_ll);
			struct_free(*cmds);
			exit (EXIT_FAILURE);
		}
		ft_transfer_ll_to_ptr(cmds);
		// char *str = find_node(cmds, "TERM");
		// printf("TERM=%s\n", str);
		execve(path, cmds->scmd[i].cmd, cmds->envp);
	}
	else
	{
		close_fds(cmds, fd);
		struct_free(*cmds);
		// ft_free_list(cmds->env_ll);
	}
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
	if (waitpid(pid, &cmds->exit_status, 0) == -1)
		return(0);
	dup2(initial_stdin, STDIN_FILENO);
	close (initial_stdin);
	close (fd[0]);
	close (fd[1]);
	return (1);
}

int	piping_root(t_compound *cmds)
{
	if (cmds->nbr_scmd == 1 && is_built_in(cmds->scmd[0].cmd[0]))
	{
		if_builtin_execute(cmds, &cmds->scmd[0]);
	}	
	else if (!piping(cmds))
		return (0);

	return (1);

}