/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2023/12/15 17:10:23 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	cleanup(t_list *m, int status)
{
	if (m)
	{
		if (m->path)
			(free(m->path), m->path = NULL);
	}
	if (status == EXIT)
		exit (EXIT_FAILURE);
}

void	ft_write_error(int status, char *str)
{
	
	if (status == CANT_OPEN)
	{
		write(2, "minishell: ", 11);
		write(2, "no such file or directory: ", 28);
		write(2, str, ft_strlen(str));
	}
	else if (status == NOT_ENOUGH_ARGUMENTS)
	{
		write(2, str, ft_strlen(str));
		write(2, ": not enough arguments", 22);
	}
	else if (status == CMD_NOT_FOUND)
	{
		write(2, "minishell: ", 11);
		write(2, "command not found: ", 19);
		write(2, str, ft_strlen(str));
	}
	write(2, "\n", 1);
}
