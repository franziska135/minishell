/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_malloc_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:58:33 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 16:58:35 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of_token(char **tokens, int i)
{
	int	j;
	int	status;
	int	ret;

	j = 0;
	ret = 0;
	status = 0;
	while (tokens[i][j])
	{
		if (!status && (tokens[i][j] != ' ' || !in_quot(tokens[i], j)))
		{
			ret++;
			status = 1;
		}
		else if (tokens[i][j] == ' ' && !in_quot(tokens[i], j))
			status = 0;
		j++;
	}
	return (ret);
}

static size_t	malloc_size(char **tokens, int i)
{
	size_t	len;

	len = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			return (len);
		else if (tokens[i][0] == '>' || tokens[i][0] == '<')
			i++;
		else
			len += size_of_token(tokens, i);
		if (tokens[i])
			i++;
	}
	return (len);
}

int	malloc_struct(t_compound *cmds, char **tokens)
{
	size_t	i;
	size_t	len;
	int		pipe;

	i = 0;
	pipe = 0;
	len = 0;
	while (tokens[i])
	{
		len = malloc_size(tokens, i);
		if (len == 0)
			cmds->scmd[pipe].cmd = NULL;
		else
		{
			cmds->scmd[pipe].cmd = (char **)malloc(sizeof(char *) * (len + 1));
			if (!cmds->scmd[pipe].cmd)
				return (struct_free(*cmds), dpointer_free(tokens), 0);
			cmds->scmd[pipe].cmd[len] = NULL;
		}
		while (tokens[i + 1] && tokens[i][0] != '|')
			i++;
		pipe++;
		i++;
	}
	return (1);
}
