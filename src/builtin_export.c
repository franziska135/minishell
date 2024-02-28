/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:09 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_key_and_value(char **key, char **value, char *current_cmd)
{
	*key = save_key(current_cmd);
	if (!key)
		return (FALSE);
	if (equal_sign_and_value(current_cmd) == 2)
	{
		*value = save_value(current_cmd);
		if (!value)
			return (FALSE);
	}
	return (TRUE);
}
void	check_pwd_display(t_env *node)
{
	char	pwd[500];
	char	*value;

	value = getcwd(pwd, 500);
	if (node->env_display == 2)
	{
		if (node->value)
				free(node->value);
		node->value = ft_strdup(value);
	}
		node->env_display = TRUE;
}

//if there is an equal sign but no value, variable is set to null
//if there is an equal sign and value, variable is set to value
//if no equal sign, nothing happes to the existing variable
int	adapt_node(t_compound *cmds, char *current_cmd, char *key, char *value)
{
	t_env	*new_node;

	new_node = find_node(cmds, key);
	if (equal_sign_and_value(current_cmd) != 0)
	{
		if (equal_sign_and_value(current_cmd) == 1)
		{
			if (new_node->value)
				free(new_node->value);
			new_node->value = NULL;
			new_node->env_display = TRUE;
		}
		else if (equal_sign_and_value(current_cmd) == 2)
		{
			if (new_node->value)
				free(new_node->value);
			new_node->value = ft_strdup(value);
			if (!new_node->value)
				return (FALSE);
			new_node->env_display = TRUE;
		}
	}
	else if (ft_strncmp(new_node->key, "PWD", 4) == 0)
		check_pwd_display(new_node);
	return (TRUE);
}

//if there is no equal sign: variable is created and added to export only
//if there is an equal sign but no value, variable is created and added to both
//if there is an equal sign and value, variable added to both
int	new_node(t_compound *cmds, char *current_cmd, char *key, char *value)
{
	t_env	*new_node;

	new_node = ft_new_env_node(key, NULL, TRUE);
	if (!new_node)
		return (FALSE);
	if (equal_sign_and_value(current_cmd) == 0)
		new_node->env_display = FALSE;
	if (equal_sign_and_value(current_cmd) == 1)
		new_node->value = NULL;
	else if (equal_sign_and_value(current_cmd) == 2)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), FALSE);
	}
	ft_add_last_node(&cmds->env_ll, new_node);
	return (TRUE);
}

int	export_loop(t_compound *cmds, char *key, char *value, char *current_cmd)
{
	if (save_key_and_value(&key, &value, current_cmd) == FALSE)
		return (free_export(key, value), FALSE);
	if (find_node(cmds, key) != NULL)
	{
		if (adapt_node(cmds, current_cmd, key, value) == FALSE)
			return (free_export(key, value), FALSE);
	}
	else
	{
		if (new_node(cmds, current_cmd, key, value) == FALSE)
			return (free_export(key, value), FALSE);
	}
	free(key);
	if (value)
		free(value);
	key = NULL;
	value = NULL;
	return (TRUE);
}

//if variable exists the node is amended
//if variable does not exists it is created
int	builtin_export(t_compound *cmds, t_simple *scmd)
{
	char	*key;
	char	*value;
	int		i;

	key = NULL;
	value = NULL;
	i = 1;
	set_status(cmds, 0);
	if (!scmd->cmd[1])
	{
		print_export(cmds->env_ll);
		return (TRUE);
	}
	while (scmd->cmd[i])
	{
		if (export_error_check(cmds, scmd->cmd[i]) != FALSE)
		{
			if (export_loop(cmds, key, value, scmd->cmd[i]) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
