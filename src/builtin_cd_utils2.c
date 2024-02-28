/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:43 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flag_pwd(t_compound *cmds)
{
	t_env	*node;
	char	pwd[500];
	char	*storage;

	node = find_node(cmds, "PWD");
	if (node)
	{
		storage = getcwd(pwd, 500);
		if (!storage)
			return ;
		if (node->value)
			free(node->value);
		node->value = ft_strdup(storage);
		if (node->env_display == 3)
			node->env_display = 2;
	}
}
