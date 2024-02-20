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

//add checks for key/value = NULL -> what would that mean?
//if one of them null, no variable value??
t_env	*ft_new_env_node(char *key, char *value, int env_display)
{
	t_env	*ptr;

	ptr = (t_env *)malloc(sizeof(t_env));
	if (!(ptr))
		return (NULL);
	ptr->key = ft_strdup(key);
	if (!ptr->key)
		return (free(ptr), NULL);
	if (value)
	{
		ptr->value = ft_strdup(value);
		if (!ptr->value)
			return (free(ptr->key), free(ptr), NULL);
	}
	else
		ptr->value = NULL;
	ptr->env_display = env_display;
	ptr->next = NULL;
	return (ptr);
}

void	ft_add_last_node(t_env **lst, t_env *new_node)
{
	t_env	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

//find the = delimiter for key and value to split them
size_t	iterate_ultil_equal(const char *envp_i)
{
	int	i;

	i = 0;
	while (envp_i[i] && envp_i[i] != '=')
		i++;
	return (i);
}

int	ft_init_ll_loop(t_compound *cmds, char **envp, t_env *new_node, int i)
{
	char	*key;
	char	*value;
	size_t	equal_sing;

	key = NULL;
	value = NULL;
	equal_sing = iterate_ultil_equal(envp[i]);
	key = ft_substr(envp[i], 0, equal_sing);
	if (!key)
		return (0);
	value = ft_substr(envp[i], equal_sing + 1, ft_strlen(envp[i]) - equal_sing);
	if (!value)
		return (free(key), 0);
	new_node = ft_new_env_node(key, value, TRUE);
	if (!new_node)
		return (free(key), free(value), free(new_node), 0);
	ft_add_last_node(&cmds->env_ll, new_node);
	if (value)
		(free(value), value = NULL);
	if (key)
		(free(key), key = NULL);
	return (TRUE);
}

//a copy of the environment stored in a linked list
int	init_env_llist(t_compound *cmds, char **envp)
{
	t_env	*new_node;
	int		i;

	cmds->envp = NULL;
	cmds->env_ll = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_init_ll_loop(cmds, envp, new_node, i) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		i++;
	}
	return (1);
}
