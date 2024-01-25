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
#include "execute.h"

//add checks for key/value = NULL -> what would that mean?
//if one of them null, no variable value??
t_env	*ft_new_env_node(char *key, char *value)
{
	t_env	*ptr;

	ptr = (t_env *)malloc(sizeof(t_env));
	if (!(ptr))
		return (NULL);
	ptr->key = key;
	ptr->value = value;
	// printf("key:%s\n", ptr->key);
	// printf("value:%s\n", ptr->value);
	ptr->next = NULL;
	return (ptr);
}

void	ft_add_last_node(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

//find the = delimiter for key and value to split them
size_t	iterate_ultil_equal(const char *envp_i)
{
	int	i;

	i = 0;
	while (envp_i[i] && envp_i[i] != '=')
		i++;
	return (i + 1);
}

//a copy of the environment stored in a linked list
//add NULL checks for substr and new_env_node
void	init_env_llist(t_compound *cmds, char **envp)
{
	t_env	*new_node;
	t_env	*head;
	char	*key;
	char	*value;
	size_t	i_equal_sign;
	int		i;

	key = NULL;
	value = NULL;
	head = NULL;
	i = 0;
	cmds->envp = envp;
	while(envp[i])
	{
		i_equal_sign = iterate_ultil_equal(envp[i]);
		key = ft_substr(envp[i], 0, i_equal_sign);
		value = ft_substr(envp[i], i_equal_sign, ft_strlen(envp[i]) - i_equal_sign);
		new_node = ft_new_env_node(key, value);
		ft_add_last_node(&head, new_node);
		i++;
	}
	//i cant free key and value can i?
	//i can free if i use strdup on both every time, but that creates even more trouble doesnt it?
	// free (key);
	cmds->env_ll = head;
}