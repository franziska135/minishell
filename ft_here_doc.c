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

int	ft_here_doc(char *delimiter)
{
	int		fd[2];
	char	*gnl;

	if (pipe(fd) == -1)
		return (-1);
	gnl = get_next_line(STDIN_FILENO);
	if (gnl && gnl[ft_strlen(gnl) - 1] == '\n')
		gnl[ft_strlen(gnl) - 1] = '\0';
	while (gnl && ft_strncmp(delimiter, gnl, ft_strlen(gnl) + 1) != 0)
	{
		write (fd[1], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
		if (gnl && gnl[ft_strlen(gnl) - 1] == '\n')
			gnl[ft_strlen(gnl) - 1] = '\0';
	}
	free(gnl);
	close (fd[1]);

	return (fd[0]);
}
