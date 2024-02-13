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

// static char	**expand_redir(t_compound *cmds, char *token)
// {
// 	char	*new_token;
// 	char	*new_token;
// 	char	*ret;
// 	char	**split_token;

// 	new_token = expand_redir(cmds, token);
// 	if (!new_token)
// 		return (NULL);
// 	split_token = expansion_split(new_token);
// 	free(new_token);
// 	if (!split_token)
// 		return (NULL);
// 	if (!split_token[0] || split_token[1])
// 	{
// 		dpointer_free(split_token);
// 		return (NULL);
// 	}
// 	split_token[0] = remove_quotes(split_token[0]);
// 	return (split_token);
// }

static void	redir_out(t_compound *cmds, char *file, int pipe, size_t *i)
{
	char	**str;

	*i += 1;
	if (cmds->scmd[pipe].out_fd == -1 || cmds->scmd[pipe].in_fd == -1)
		cmds->scmd[pipe].out_fd = -1;
	if (cmds->scmd[pipe].out_fd)
		close (cmds->scmd[pipe].out_fd);
	str = expand_redir(cmds, file);
	if (!str)
	{
		print_error(NULL, file, "ambiguous redirect");
		cmds->scmd[pipe].out_fd = -1;
	}
	else
	{
		cmds->scmd[pipe].out_fd = open(*str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (cmds->scmd[pipe].out_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}

static void	redir_in(t_compound *cmds, char *file, int pipe, size_t *i)
{
	char	**str;

	*i += 1;
	if (cmds->scmd[pipe].out_fd == -1 || cmds->scmd[pipe].in_fd == -1)
		cmds->scmd[pipe].in_fd = -1;
	if (cmds->scmd[pipe].in_fd)
		close (cmds->scmd[pipe].in_fd);
	str = expand_redir(cmds, file);
	if (!str)
	{
		print_error(NULL, file, "ambiguous redirect");
		cmds->scmd[pipe].in_fd = -1;
	}
	else
	{
		cmds->scmd[pipe].in_fd = open(*str, O_RDONLY);
		if (cmds->scmd[pipe].in_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}

static void	redir_append(t_compound *cmds, char *file, int pipe, size_t *i)
{
	char	**str;

	*i += 1;
	if (cmds->scmd[pipe].out_fd == -1 || cmds->scmd[pipe].in_fd == -1)
		cmds->scmd[pipe].out_fd = -1;
	if (cmds->scmd[pipe].out_fd)
		close (cmds->scmd[pipe].out_fd);
	str = expand_redir(cmds, file);
	if (!str)
	{
		print_error(NULL, file, "ambiguous redirect");
		cmds->scmd[pipe].out_fd = -1;
	}
	else
	{
		cmds->scmd[pipe].out_fd = open(*str, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (cmds->scmd[pipe].out_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}



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
		else if (!ft_strncmp(tokens[i], ">", 2) && cmds->scmd[pipe].out_fd != -1)
			redir_out(cmds, tokens[i + 1], pipe, &i);
		else if (!ft_strncmp(tokens[i], "<", 2) && cmds->scmd[pipe].in_fd != -1)
			redir_in(cmds, tokens[i + 1], pipe, &i);
		else if (!ft_strncmp(tokens[i], ">>", 3) && cmds->scmd[pipe].out_fd != -1)
			redir_append(cmds, tokens[i + 1], pipe, &i);
		i++;
	}
	return (tokens);
}
