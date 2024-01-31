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

void	print_export(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		write (1, "dexlare -x ", 11);
		write(1, current->key, ft_strlen(current->key));
		if (current->env_display == TRUE)
		{
			write (1, "=", 1);
			write (1, "\"", 2);
			if (current->value)
				write(1, current->value, ft_strlen(current->value));
			write (1, "\"", 2);
		}
		write (1, "\n", 1);
		current = current->next;
	}
}

int	save_key_and_value(char **key, char **value, t_simple *scmd)
{
	*key = save_key(scmd->cmd[1]);
	if (!key)
		return (FALSE);
	if (equal_sign_and_value(scmd->cmd[1]) == 2)
	{
		*value = save_value(scmd->cmd[1]);
		if (!value)
			return (FALSE);
	}
	return (TRUE);
}

//if there is an equal sign but no value, variable is set to null
//if there is an equal sign and value, variable is set to value
//if no equal sign, nothing happes to the existing variable
int	adapt_node(t_compound *cmds, t_simple *scmd, char *key, char *value)
{
	t_env	*new_node;

	write(1, "node found: \t\t", 14);
	new_node = find_node(cmds, key);
	if (equal_sign_and_value(scmd->cmd[1]) != 0)
	{
		if (equal_sign_and_value(scmd->cmd[1]) == 1)
		{
			if (new_node->value)
				free(new_node->value);
			new_node->value = NULL;
			new_node->env_display = TRUE;
			write (1, "existing variable set to null in env and export\n", 48);
		}
		else if (equal_sign_and_value(scmd->cmd[1]) == 2)
		{
			if (new_node->value)
				free(new_node->value);
			new_node->value = ft_strdup(value);
			if (!new_node->value)
				return (FALSE);
			new_node->env_display = TRUE;
			write (1, "existing variable set to new value in env and export\n", 53);
		}
	}
	else
		write(1, "nothing happened to the existing variable\n", 42);
	return (TRUE);
}

//if there is no equal sign: variable is created and added to export only
//if there is an equal sign but no value, variable is created and added to both
//if there is an equal sign and value, variable added to both
int	new_node(t_compound *cmds, t_simple *scmd, char *key, char *value)
{
	t_env	*new_node;

	write(1, "node didnt exist yet: \t", 23);
	new_node = ft_new_env_node(key, NULL, TRUE);
	if (!new_node)
		return (FALSE);
	if (equal_sign_and_value(scmd->cmd[1]) == 0)
	{
		new_node->env_display = FALSE;
		write (1, "new empty variable added only to export\n", 40);
	}
	if (equal_sign_and_value(scmd->cmd[1]) == 1)
	{
		new_node->value = NULL;
		write (1, "new empty variable added to env and export\n", 43);
	}
	else if (equal_sign_and_value(scmd->cmd[1]) == 2)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), FALSE);
		write (1, "new full val added to env and export\n", 37);
	}
	ft_add_last_node(&cmds->env_ll, new_node);
	return (TRUE);
}

//if variable exists the node is amended
//if variable does not exists its created
int	builtin_export(t_compound *cmds, t_simple *scmd)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (export_error_check(cmds, scmd) == FALSE)
		return (FALSE);
	if (save_key_and_value(&key, &value, scmd) == FALSE)
		return (free_export(key, value), FALSE);
	if (find_node(cmds, key) != NULL)
	{
		if (adapt_node(cmds, scmd, key, value) == FALSE)
			return (free_export(key, value), FALSE);
	}
	else
	{
		if (new_node(cmds, scmd, key, value) == FALSE)
			return (free_export(key, value), FALSE);
	}
	free(key);
	if (value)
		free(value);
	key = NULL;
	value = NULL;
	return (TRUE);
}
