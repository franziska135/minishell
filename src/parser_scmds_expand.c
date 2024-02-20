/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 15:24:47 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**read_n_split(int *fd, int *fd_flag)
{
	char	*gnl;
	char	*gnl_flag;
	char	**split;

	write(fd[1], "\0", 1);
	close(fd[1]);
	write(fd_flag[1], "\0", 1);
	close(fd_flag[1]);
	gnl = get_next_line(fd[0]);
	close(fd[0]);
	if (!gnl || gnl[0] == '\0')
		return (free(gnl), NULL);
	gnl_flag = get_next_line(fd_flag[0]);
	close(fd_flag[0]);
	if (!gnl_flag || gnl_flag[0] == '\0')
		return (free(gnl), NULL);
	split = expansion_split(gnl, gnl_flag);
	free(gnl);
	free(gnl_flag);
	return (split);
}

char	**scmds_expand(t_compound *cmds, char **scmds)
{
	int	fd[2];
	int	fd_flag[2];
	int	i;
	int	flag;

	if (pipe(fd) == -1)
		return (dpointer_free(scmds), NULL);
	if (pipe(fd_flag) == -1)
		return (dpointer_free(scmds), close (fd[0]), close(fd[1]), NULL);
	i = 0;
	while (scmds && scmds[i])
	{
		flag = expand_token(cmds, scmds[i], fd, fd_flag);
		write(fd[1], " ", 1);
		ft_putnbr_fd(flag, fd_flag[1]);
		i++;
	}
	dpointer_free(scmds);
	return (read_n_split(fd, fd_flag));
}
