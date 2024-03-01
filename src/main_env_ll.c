/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env_ll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:53 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates a copy of envp stored in a linked list
int	init_env_llist(t_compound *cmds, char **envp)
{
	t_env	*new_node;
	char	pwd[500];
	char	*storage;
	int		i;

	cmds->envp = NULL;
	cmds->env_ll = NULL;
	new_node = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_init_ll_loop(cmds, envp, new_node, i) == FALSE)
			return (print_error(NULL, NULL, strerror(errno)), FALSE);
		i++;
	}
	initiate_static_env_variables(cmds);
	storage = getcwd(pwd, 500);
	cmds->pwd = ft_strdup(storage);
	cmds->envp = FALSE;
	if (find_node(cmds, "PATH") == NULL)
		cmds->envp = TRUE;
	return (1);
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

//in case envp -i (no env), these var are set
int	initiate_static_env_variables2(t_compound *cmds)
{
	t_env	*new_node;

	new_node = find_node(cmds, "_");
	if (new_node)
	{
		if (adapt_node(cmds, "_=env", "_", "/usr/bin/env") == FALSE)
			return (FALSE);
	}
	else
	{
		new_node = ft_new_env_node("_", "/usr/bin/env", TRUE);
		if (!new_node)
			return (FALSE);
		ft_add_last_node(&cmds->env_ll, new_node);
	}
	return (TRUE);
}

int	initiate_static_env_variables3(t_compound *cmds)
{
	t_env	*new_node;
	int		number;
	char	*number2;

	new_node = find_node(cmds, "SHLVL");
	if (new_node)
	{
		number = ft_atoi(new_node->value) + 1;
		number2 = ft_itoa(number);
		if (adapt_node(cmds, "SHLVL=1", "SHLVL", number2) == FALSE)
			return (free (number2), FALSE);
		free (number2);
	}
	else
	{
		new_node = ft_new_env_node("SHLVL", "1", TRUE);
		if (!new_node)
			return (FALSE);
		ft_add_last_node(&cmds->env_ll, new_node);
	}
	return (TRUE);
}

//in case envp -i (no env), these var are set
int	initiate_static_env_variables(t_compound *cmds)
{
	t_env	*new_node;
	char	pwd[100];

	if (find_node(cmds, "OLDPWD") == NULL)
	{
		new_node = ft_new_env_node("OLDPWD", NULL, FALSE);
		if (!new_node)
			return (FALSE);
		ft_add_last_node(&cmds->env_ll, new_node);
	}
	if (find_node(cmds, "PWD") == NULL)
		update_env_ll(cmds, "PWD", getcwd(pwd, 100));
	if (initiate_static_env_variables2(cmds) == FALSE)
		return (FALSE);
	if (initiate_static_env_variables3(cmds) == FALSE)
		return (FALSE);
	return (TRUE);
}
