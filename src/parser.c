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

static size_t	pipe_count(char **tokens)
{
	size_t	i;
	size_t	nbr_pipe;

	i = 0;
	nbr_pipe = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			nbr_pipe++;
		i++;
	}
	return (nbr_pipe);
}

char	**parser(t_compound *cmds, char **tokens)
{
	cmds->nbr_scmd = pipe_count(tokens) + 1;
	cmds->scmd = (t_simple *)malloc(sizeof(t_simple) * cmds->nbr_scmd);
	struct_nullifier(cmds);
	cmds->nbr_scmd = pipe_count(tokens) + 1;
	tokens = open_redir(cmds, tokens);
	if (!struct_cpy(cmds, tokens))
		return (0);
	return (tokens);
}
