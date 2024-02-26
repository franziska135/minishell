/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:56 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/26 15:31:58 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_eof_hd(char *delim, int *fd)
{
	write (2, "fzsh: warning: here-document at ", 34);
	write (2, "line 1 delimited by end-of-file (wanted `", 42);
	write (2, delim, ft_strlen(delim));
	write (2, "')\n", 4);
}

void	finish_hd(char *gnl, int fd[2])
{
	free(gnl);
	if (g_signal != 0)
	{
		close (fd[0]);
		fd[0] = -1;
	}
	close (fd[1]);
}
