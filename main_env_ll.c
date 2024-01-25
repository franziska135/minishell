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
	//but free ptr and key;
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

//a copy of the environment stored in a linked list
//add NULL checks for substr and new_env_node
int	init_env_llist(t_compound *cmds, char **envp)
{
	t_env	*new_node;
	t_env	*head;
	char	*key;
	char	*value;
	size_t	equal_sing;

	key = NULL;
	value = NULL;
	int i;

	head = NULL;
	i = 0;
	while(envp[i])
	{
		equal_sing = iterate_ultil_equal(envp[i]);
		key = ft_substr(envp[i], 0, equal_sing);
		if (!key)
			return (0);
		value = ft_substr(envp[i], equal_sing + 1, ft_strlen(envp[i]) - equal_sing);
		if (!value)
			return (free(key), 0);
		new_node = ft_new_env_node(key, value, TRUE);
		if (!new_node)
			return (free(key), free(new_node), 0);
		ft_add_last_node(&head, new_node);
		i++;
	}
	free (key);
	free(value);
	cmds->env_ll = head;
	return (1);
}
