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
	t_env *current;
	
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

char	*save_key(char *cmd1)
{
	int		i;
	char	*key;

	key = NULL;
	i = 0;

	while (cmd1[i] != '=' && cmd1[i] != '\0')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (cmd1[i] != '=' && cmd1[i] != '\0')
	{
		key[i] = cmd1[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

//function is just called after a check whether a value exists
char	*save_value(char *cmd1)
{
	int		i;
	int		lenght_value;
	char	*value;

	value = NULL;
	i = 0;
	lenght_value = 0;
	while (cmd1[i] != '=' && cmd1[i] != '\0')
		i++;
	i++;
	while (cmd1[i + lenght_value] != '\0')
		lenght_value++;
	value = (char *)malloc(sizeof(char) * (lenght_value + 1));
	if (!value)
		return (NULL);
	lenght_value = 0;
	while (cmd1[i + lenght_value] != '\0')
	{
		value[lenght_value] = cmd1[i + lenght_value];
		lenght_value++;
	}
	value[lenght_value] = '\0';
	return (value);
}

//returns 0 if just key
//returns 1 if key and equal sign
//returns 2 if key and equal sign and value
int	equal_sign_and_value(char *cmd1)
{
	int i;

	i = 0;
	while (cmd1[i] != '\0' && cmd1[i] != '=')
		i++;
	if (cmd1[i] == '\0')
		return (0);
	if (cmd1[i] == '=' && cmd1[i + 1] == '\0')
		return (1);
	else
		return (2);
	}

int		export_error_check(t_compound *cmds, t_simple *scmd)
{
	if (!scmd->cmd[1])
	{
		print_export(cmds->env_ll);
		return (FALSE);
	}
	else if (ft_strncmp(scmd->cmd[1], "=", 1) == 0)
	{
		print_error("minishell: ", "export: ", scmd->cmd[1], "not a valid identifier");
		return (FALSE);
	}
	return (TRUE);
}

int		save_key_and_value(char **key, char **value, t_simple *scmd)
{
	*key = save_key(scmd->cmd[1]);
//malloc
	if (!key)
		return (FALSE);
	if (equal_sign_and_value(scmd->cmd[1]) == 2) // 2 if there is value
	{
//malloc and free key
		*value = save_value(scmd->cmd[1]);
//return if malloc failed --> if null returend
		if (!value)
			return (FALSE);
	}
	return (TRUE);
}

int		adapt_existing_variable(t_compound *cmds, t_simple *scmd, char *key, char *value)
{
	t_env	*new_node;

	write(1, "node found: \t\t", 14);
	new_node = find_node(cmds, key);
	//if equal sign --> return not 0
	if (equal_sign_and_value(scmd->cmd[1]) != 0)
	{
		//if equal sign and no value --> return 1
		if (equal_sign_and_value(scmd->cmd[1]) == 1)
		{
			if (new_node->value)
				free(new_node->value);
			new_node->value = NULL;
			new_node->env_display = TRUE;
			write (1, "existing variable set to null in env and export\n", 48);
		}
		//if equal sign and value --> return 2
		else if (equal_sign_and_value(scmd->cmd[1]) == 2)
		{
			if (new_node->value)
				free(new_node->value);
			new_node->value = ft_strdup(value);
//malloc free key and if value exists value
			if (!new_node->value)
				return (FALSE);
			new_node->env_display = TRUE;
			write (1, "existing variable set to new value in env and export\n", 53);
		}
	}
		else
			write(1, "nothing happened to the existing variable\n", 42);
		//else: if no equal sign nothing happens
	return (TRUE);
}

int		adapt_new_variable(t_compound *cmds, t_simple *scmd, char *key, char *value)
{
	t_env	*new_node;

	write(1, "node didnt exist yet: \t", 23);
	//create new node with key = key
	new_node = ft_new_env_node(key, NULL, TRUE);
//malloc but free key and value if it exists
	if (!new_node)
		return (FALSE);
	//if no equal sign
	if (equal_sign_and_value(scmd->cmd[1]) == 0)
	{
		new_node->env_display = FALSE;
		write (1, "new empty variable added only to export\n", 42);
	}
	//if equal sign and no value -> return 1
	if (equal_sign_and_value(scmd->cmd[1]) == 1)
	{
		new_node->value = NULL;
		write (1, "new empty variable added to env and export\n", 43);
	}
	//if equal sign and value -> return 2
	else if (equal_sign_and_value(scmd->cmd[1]) == 2)
	{
		new_node->value = ft_strdup(value);
//malloc but free key and malloc
		if (!new_node->value)
			return (free(new_node->key), FALSE);
		write (1, "new full val added to env and export\n", 37);
	}
	ft_add_last_node(&cmds->env_ll, new_node);
	return (TRUE);
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
	//if variable exists
	if (find_node(cmds, key) != NULL)
	{
		if (adapt_existing_variable(cmds, scmd, key, value) == FALSE)
			return (free_export(key, value), FALSE);
	}
	//if node does not exist yet
	else
	{
		if (adapt_new_variable(cmds, scmd, key, value) == FALSE)
			return (free_export(key, value), FALSE);
	}
	free(key);
	if (value)
		free(value);
	key = NULL;
	value = NULL;
	return (TRUE);
}
