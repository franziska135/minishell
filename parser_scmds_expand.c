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

char	**scmds_expand(t_compound *cmds, char **scmds)
{
	int		fd[2];
	int		i;
	char	*gnl;
	char	**split;

	if (pipe(fd) == -1)
		return (dpointer_free(scmds), NULL);
	i = 0;
	while (scmds && scmds[i])
	{
		expand_token(cmds, scmds[i], fd);
		write(fd[1], " ", 1);
		i++;
	}
	dpointer_free(scmds);
	write(fd[1], "\0", 1);
	close(fd[1]);
	gnl = get_next_line(fd[0]);
	close(fd[0]);
	if (!gnl || gnl[0] == '\0')
		return (free(gnl), NULL);
	split = expansion_split(gnl);
	free(gnl);
	return (split);
}
