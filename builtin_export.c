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

//function is jsut called if there esists a value
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

void	builtin_export(t_compound *cmds, t_simple *scmd)
{
	int		i;
	t_env	*new_node;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (!scmd->cmd[1])
	{
		print_export(cmds->env_ll);
		return ;
	}
	else if (ft_strncmp(scmd->cmd[1], "=\0", 2) == 0)
		print_error("minishell: ", "export: ", "'='", "not a valid identifier");
	//create node if variable does not exist yet
	key = save_key(scmd->cmd[1]);
//malloc
	if (!key)
		return ;
	if (equal_sign_and_value(scmd->cmd[1]) == 2) // 2 if there is value
	{
//malloc and free key
		value = save_value(scmd->cmd[1]);
		//return if malloc failed --> if null returend
		if (!value)
			return ;
	}
	//if variable exists
	if (find_node(cmds, key) != NULL)
	{
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
				write (1, "existing variable set to a null terminator in env and export\n", 61);
			}
			//if equal sign and value --> return 2
			else if (equal_sign_and_value(scmd->cmd[1]) == 2)
			{
				if (new_node->value)
					free(new_node->value);
				new_node->value = ft_strdup(value);
//malloc free key and if value exists value
				if (!new_node->value)
					return ;
				new_node->env_display = TRUE;
				write (1, "existing variable set to new value in env and export\n", 53);
			}
		}
		else
			write(1, "nothing happened to the existing variable\n", 42);
		//else: if no equal sign nothing happens
	}
	//if node does not exist yet
	else
	{
		write(1, "node didnt exist yet: \t", 23);
		//create new node with key = key
		new_node = ft_new_env_node(key, NULL, TRUE);
//malloc but free key and value if it exists
		if (!new_node)
			return ;
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
				return ;
			write (1, "new full val added to env and export\n", 37);
		}
		ft_add_last_node(&cmds->env_ll, new_node);
	}
	free(key);
	if (value)
		free(value);
	key = NULL;
	value = NULL;
}