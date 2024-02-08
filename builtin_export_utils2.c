/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 13:54:46 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//returns a pointer to the node storing the key and the variable
//returns NULL if key not found
t_env	*find_node(t_compound *cmds, char *needle)
{
	t_env	*haystack;
	char	*str;
	size_t	h_length;

	h_length = 0;
	haystack = cmds->env_ll;
	while (haystack)
	{
		h_length = ft_strlen(haystack->key) + 1;
		if (ft_strncmp(haystack->key, needle, h_length) == 0)
			return (haystack);
		haystack = haystack->next;
	}
	return (NULL);
}

//make sure that nothing gets updated in case the variable doesnt exist
//check for if new value == NULL;
////!!!!!CHECK FOR NEW VALUIE == NULL;
//error if node is unset and not found?
int	update_env_ll(t_compound *cmds, char *variable, char *new_value)
{
	t_env	*node;

	if (new_value && variable)
	{
		node = find_node(cmds, variable);
		if (node)
		{
			free(node->value);
			node->value = ft_strdup(new_value);
			if (!node->value)
				return (FALSE);
		}
		else if (!node)
		{
			node = ft_new_env_node(variable, new_value, TRUE);
			if (!node)
				return (FALSE);
			ft_add_last_node(&cmds->env_ll, node);
		}
	}
	return (TRUE);
}
