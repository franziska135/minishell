/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipin_root.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:15:18 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cl_ch(t_compound *cmds, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close_fds(cmds);
	struct_free(*cmds);
	dpointer_free(cmds->envp);
	cleanup_envp_ll(cmds->env_ll);
	exit(cmds->exit_status);
}

static void	child_process(t_compound *cmds, int *fd, size_t i, int initial_stdin)
{
	char	*path;

	close(initial_stdin);
	if (cmds->scmd[i].in_fd != -1 && cmds->scmd[i].out_fd != -1
		&& cmds->scmd[i].cmd)
	{
		if (cmds->scmd[i].out_fd != 0)
			dup2(cmds->scmd[i].out_fd, STDOUT_FILENO);
		else if (i != cmds->nbr_scmd - 1)
			dup2(fd[1], STDOUT_FILENO);
		close_fds(cmds);
		if (is_built_in(cmds->scmd[i].cmd[0]))
			(if_builtin_execute(cmds, &cmds->scmd[i], -1, fd), cl_ch(cmds, fd));
		path = path_finder(cmds, i);
		if (!path)
		{
			cmds->exit_status = 127;
			cl_ch(cmds, fd);
		}
		if (!ft_transfer_ll_to_env_ptr(cmds))
			exit(1);
		(close(fd[0]), close(fd[1]));
		(execve(path, cmds->scmd[i].cmd, cmds->envp), which_error(cmds, path));
	}
	cl_ch(cmds, fd);
}

static int	parent_process(t_compound *cmds, int *fd, int *pid, int std_in)
{
	size_t	i;

	i = 0;
	while (i < cmds->nbr_scmd)
	{
		if (pipe(fd) == -1)
			return (close_fds(cmds), close(std_in), 0);
		if (cmds->scmd[i].in_fd > 2)
			(dup2(cmds->scmd[i].in_fd, 0), close(cmds->scmd[i].in_fd));
		signal_inhibition(cmds);
		pid[i] = fork();
		if (pid[i] == -1)
			return (fork_fail(cmds, fd, std_in), 0);
		if (pid[i] == 0)
		{
			non_interactive_mode(cmds);
			child_process(cmds, fd, i, std_in);
		}
		close(fd[1]);
		if (i < (cmds->nbr_scmd - 1) && cmds->scmd[i + 1].in_fd == 0)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (cmds->scmd[i].out_fd > 2)
			close(cmds->scmd[i].out_fd);
		i++;
	}
	// non_interactive_mode(cmds);
	return (1);
}

static int	piping(t_compound *cmds)
{
	int		fd[2];
	size_t	i;
	int		pid[1024];
	int		initial_stdin;

	initial_stdin = dup(STDIN_FILENO);
	if (!parent_process(cmds, fd, pid, initial_stdin))
		return (struct_free(*cmds), 0);
	dup2(initial_stdin, STDIN_FILENO);
	close(initial_stdin);
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (i < cmds->nbr_scmd -1)
	{
		if (waitpid(pid[i], NULL, 0) == -1)
			return (0);
		i++;
	}
	if (waitpid(pid[i], &cmds->exit_status, 0) == -1)
		return (0);
	return (1);
}

int	piping_root(t_compound *cmds)
{
	int	initial_stdout;

	if (cmds->nbr_scmd == 1 && cmds->scmd[0].cmd
		&& is_built_in(cmds->scmd[0].cmd[0])
		&& cmds->scmd[0].in_fd != -1 && cmds->scmd[0].out_fd != -1)
	{
		initial_stdout = dup(STDOUT_FILENO);
		if (cmds->scmd[0].in_fd > 2)
			close(cmds->scmd[0].in_fd);
		if (cmds->scmd[0].out_fd != 0)
		{
			dup2(cmds->scmd[0].out_fd, STDOUT_FILENO);
			close(cmds->scmd[0].out_fd);
		}
		if_builtin_execute(cmds, &cmds->scmd[0], initial_stdout, NULL);
		dup2(initial_stdout, STDOUT_FILENO);
		close(initial_stdout);
	}
	else if (!piping(cmds))
		return (0);
	return (1);
}
