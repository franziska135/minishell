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

int	find_envp_path(t_list *m, char *str)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(str);
	while (m->envp[i])
	{
		if (ft_strncmp(m->envp[i], str, length) == 0)
		{
			m->index_path = i;
			return (1);
		}
		i++;
	}
	//error if the env variable does not exist
	return (0);
}
