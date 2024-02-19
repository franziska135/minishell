/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2023/11/27 16:12:30 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	malloc_n_copy(t_compound *cmds, char *str, int pipe, size_t *j)
{
	cmds->scmd[pipe].cmd[*j] = (char *)
		malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cmds->scmd[pipe].cmd[*j])
		return (0);
	ft_strlcpy(cmds->scmd[pipe].cmd[*j], str, ft_strlen(str) + 1);
	*j += 1;
	return (1);
}

static int	write_struct(t_compound *cmds, char **tokens)
{
	size_t	i;
	size_t	j;
	size_t	pipe;

	i = 0;
	j = 0;
	pipe = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			pipe++;
			j = 0;
		}
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i++;
		else if (cmds->scmd[pipe].cmd)
		{
			if (!malloc_n_copy(cmds, tokens[i], pipe, &j))
				return (struct_free(*cmds), dpointer_free(tokens), 0);
		}
		if (tokens[i])
			i++;
	}
	return (1);
}

int	struct_cpy(t_compound *cmds, char **tokens)
{
	int	i;
	int	j;

	if (!malloc_struct(cmds, tokens))
	{
		dpointer_free(tokens);
		return (0);
	}
	if (!write_struct(cmds, tokens))
	{
		struct_free(*cmds);
		dpointer_free(tokens);
		return (0);
	}
	i = 0;
	while (i < cmds->nbr_scmd)
	{
		if (cmds->scmd[i].cmd)
			cmds->scmd[i].cmd = scmds_expand(cmds, cmds->scmd[i].cmd);
		i++;
	}
	return (1);
}
