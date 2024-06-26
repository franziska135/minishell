/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:24 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_smallest(t_env *head)
{
	t_env	*smallest;
	t_env	*current;

	current = head;
	smallest = head;
	while (current)
	{
		if (ft_strncmp(current->key, smallest->key, ft_strlen(smallest->key))
			< 0)
			smallest = current;
		current = current->next;
	}
	return (smallest);
}

t_env	*find_target(t_env *head, t_env *last)
{
	t_env	*cur;
	t_env	*next;

	if (last == NULL)
		return (find_smallest(head));
	next = NULL;
	cur = head;
	while (cur)
	{
		if (ft_strncmp(cur->key, last->key, ft_strlen(cur->key)) > 0)
		{
			if (next == NULL)
				next = cur;
			else if (ft_strncmp(cur->key, next->key, ft_strlen(next->key)) < 0
				&& ft_strncmp(cur->key, last->key, ft_strlen(cur->key)) > 0)
				next = cur;
		}
		cur = cur->next;
	}
	return (next);
}

void	builtin_export_print(t_env *next_print)
{
	write (1, "declare -x ", 11);
	write(1, next_print->key, ft_strlen(next_print->key));
	if (next_print->env_display == TRUE)
	{
		(write (1, "=", 1), write (1, "\"", 1));
		if (next_print->value)
			write(1, next_print->value, ft_strlen(next_print->value));
		write (1, "\"", 1);
	}
	write (1, "\n", 1);
}

void	check_pwd_display(t_env *node)
{
	if (!node->value)
		node->env_display = FALSE;
	else if (node->value)
		node->env_display = TRUE;
}
