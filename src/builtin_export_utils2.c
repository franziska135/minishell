/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:24 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_node(t_compound *cmds, char *needle)
{
	t_env	*haystack;
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

int	update_env_ll(t_compound *cmds, char *variable, char *new_value)
{
	t_env	*node;

	if (new_value && variable)
	{
		node = find_node(cmds, variable);
		if (node)
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(new_value);
			if (!node->value)
				return (FALSE);
			node->env_display = TRUE;
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

void	print_export(t_env *head)
{
	t_env	*current;
	t_env	*next_print;
	t_env	*last_printed;

	current = head;
	next_print = NULL;
	last_printed = NULL;
	while (current)
	{
		next_print = find_target(head, last_printed);
		if (!next_print)
			return ;
		last_printed = next_print;
		if (ft_strncmp(next_print->key, "_", 2) != 0
			&& next_print->env_display < 2)
			builtin_export_print(next_print);
		current = current->next;
	}
}

void	free_export(char *key, char *value)
{
	if (key)
	{
		free(key);
		key = NULL;
	}
	if (value)
	{
		free(value);
		value = NULL;
	}
}
