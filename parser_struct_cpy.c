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

static size_t	malloc_size(char **tokens, int i)
{
	size_t	len;
	int		j;
	int		status;

	len = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			return (len);
		else if (tokens[i][0] == '>' || tokens[i][0] == '<')
			i++;
		else
		{
			j = 0;
			status = 0;
			while (tokens[i][j])
			{
				if (!status && (tokens[i][j] != ' ' || !in_quot(tokens[i], j)))
				{
					len ++;
					status = 1;
				}
				else if (tokens[i][j] == ' ' && !in_quot(tokens[i], j))
					status = 0;
				j++;
			}
		}
		if (tokens[i])
			i++;
	}
	return (len);
}

static int	malloc_struct(t_compound *cmds, char **tokens)
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

static int	write_struct(t_compound *cmds, char **tokens)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	pipe;
	char	**str;

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
			cmds->scmd[pipe].cmd[j] = (char *)malloc(sizeof(char) * (ft_strlen(tokens[i]) + 1));
			if (!cmds->scmd[pipe].cmd[j])
				return (struct_free(*cmds), dpointer_free(tokens), 0);
			ft_strlcpy(cmds->scmd[pipe].cmd[j], tokens[i], ft_strlen(tokens[i]) + 1);
			j++;
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
		{
			cmds->scmd[i].cmd = scmds_expand(cmds, cmds->scmd[i].cmd);
			j = 0;
			while (cmds->scmd[i].cmd && cmds->scmd[i].cmd[j])
			{
				cmds->scmd[i].cmd[j] = remove_quotes(cmds->scmd[i].cmd[j]);
				j++;
			}
		}
		i++;
	}
	return (1);
}
