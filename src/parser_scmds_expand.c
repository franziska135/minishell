/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scmds_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:13:12 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:13:14 by mzolfagh         ###   ########.fr       */
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
	int	fd[2][2];
	int	i;
	int	flag;

	if (pipe(fd[0]) == -1)
		return (dpointer_free(scmds), NULL);
	if (pipe(fd[1]) == -1)
		return (dpointer_free(scmds), close (fd[0][0]), close(fd[0][1]), NULL);
	i = 0;
	while (scmds && scmds[i])
	{
		flag = expand_token(cmds, scmds[i], fd);
		write(fd[0][1], " ", 1);
		ft_putnbr_fd(flag, fd[1][1]);
		i++;
	}
	dpointer_free(scmds);
	return (read_n_split(fd[0], fd[1]));
}
