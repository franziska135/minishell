/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:54:12 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_compound *cmds, int *fd)
{
	int	i;

	i = 0;
	while (i < cmds->nbr_scmd)
	{
		if (cmds->scmd[i].in_fd > 2)
			close (cmds->scmd[i].in_fd);
		if (cmds->scmd[i].out_fd > 2)
			close (cmds->scmd[i].out_fd);
		i++;
	}
}
