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

static int	if_expand(char *str)
{
	while (str && *str)
	{
		if (str[0] == '\'' || str[0] == '"')
			return (0);
		str++;
	}
	return (1);
}

static void	redir_hd(t_compound *cmds, char **tokens)
{
	size_t	i;
	int		pipe;
	int		expand;

	i = 0;
	pipe = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		if (!ft_strncmp(tokens[i], "<<", 3))
		{
			if (cmds->scmd[pipe].in_fd)
				close (cmds->scmd[pipe].in_fd);
			i++;
			expand = if_expand(tokens[i]);
			tokens[i] = remove_quotes(tokens[i]);
			cmds->scmd[pipe].in_fd = ft_here_doc(tokens[i], cmds, expand);
		}
		i++;
	}
}

char	**open_redir(t_compound *cmds, char **tokens)
{
	size_t	i;
	int		pipe;

	i = 0;
	pipe = 0;
	redir_hd(cmds, tokens);
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		else if (!ft_strncmp(tokens[i], ">", 2)
			&& cmds->scmd[pipe].out_fd != -1)
			redir_out(cmds, tokens[i + 1], pipe, &i);
		else if (!ft_strncmp(tokens[i], "<", 2) && cmds->scmd[pipe].in_fd != -1)
			redir_in(cmds, tokens[i + 1], pipe, &i);
		else if (!ft_strncmp(tokens[i], ">>", 3)
			&& cmds->scmd[pipe].out_fd != -1)
			redir_append(cmds, tokens[i + 1], pipe, &i);
		i++;
	}
	return (tokens);
}
