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
	int		fd;
	char	*gnl;

	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	gnl = get_next_line(STDIN_FILENO);
	while (gnl && ft_strncmp(delimiter, gnl, ft_strlen(gnl) != 0))
	{
		write (fd, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
	}
	free(gnl);
	close (fd);
	fd = open(".here_doc", O_RDONLY);
	return (fd);
}
