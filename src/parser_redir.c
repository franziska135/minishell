/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:12:31 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:12:35 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_out(t_compound *cmds, char *file, int pipe, size_t *i)
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
		cmds->scmd[pipe].out_fd
			= open(*str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (cmds->scmd[pipe].out_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}

void	redir_in(t_compound *cmds, char *file, int pipe, size_t *i)
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

void	redir_append(t_compound *cmds, char *file, int pipe, size_t *i)
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
		cmds->scmd[pipe].out_fd
			= open(*str, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (cmds->scmd[pipe].out_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}
