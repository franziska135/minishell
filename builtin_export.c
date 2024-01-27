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

//if VAR
//if there is no '='
	//does it exist yet? -> no?
		//add VAR to export ll
		//do nothing with envll
	//if it exists already, do nothing
//if there is an '=' -> assign value
	//if it does not exist yet
		//create new variable in env and export ll
	//if there is no value, add VAR='' to export and VAR= to env
	//if there is a value, add the value to the key

void	print_export(t_env *head)
{
	t_env *current;
	
	current = head;

	//take out
	write (2, "-------EXPORT START-------------\n", 33);
	while (current)
	{
		write (1, "dexlare -x ", 11);
		write(1, current->key, ft_strlen(current->key));
		// if (current->value)
		// {
		// 	write (1, "=", 1);
		// 	//printf("%s", current->value);
		// 	write(1, current->value, ft_strlen(current->value));
		// }
		write (1, "\n", 1);
		current = current->next;
	}
	//take out
	write (2, "-------EXPORT END-------------\n", 31);
	//newline at the end?
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

//returns null if no value or if no equal sing;
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
	// if (cmd1[i] == '\0')
	// 	return (NULL);
	// else if (cmd1[i] == '=' && cmd1[i + 1] == '\0')
	// 	return (NULL)
	i++;
	while (cmd1[i + lenght_value] != '\0')
		lenght_value++;
	value = (char *)malloc(sizeof(char) * (lenght_value + 1));
	if (!value)
		return (NULL);
	while (cmd1[i] != '\0')
	{
		value[i] = cmd1[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

int	equal_sign_and_value(char *cmd1)
{
	int i;

	while (cmd1[i] != '\0' && cmd1[i] != '=')
		i++;
	if (cmd1[i] == '\0')
		return (0); //no equal sign
	if (cmd1[i] == '=' && cmd1[i + 1] == '\0')
		return (1); //equal sign but no value;
	else
		return (2); //equal sign and value
}

//check the find node function, it doesnt check for C
//error checking
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
	//error if malloc failed
	if (!key)
		return ;
	if (equal_sign_and_value(scmd->cmd[1]) == 2) // 2 if there is value
	{
		value = save_value(scmd->cmd[1]);
		//return if malloc failed --> if null returend
		if (!value)
			return ;
	}
	//if variable exists
	if (find_node(cmds, key) != NULL)
	{
		new_node = find_node(cmds, key);
		//if equal sign --> return not 0
		if (equal_sign_and_value(scmd->cmd[1]) != 0)
		{
			//if equal sign and no value --> return 1
			if (equal_sign_and_value(scmd->cmd[1]) == 1)
			{
				//value = \0;
				new_node->value = '\0';
				//display flag 1 --> show in export and env
				new_node->env_display = TRUE;
				write (1, "existing value set to a null terminator in env and export\n", 59);
			}
			//if equal sign and value --> return 2
			else if (equal_sign_and_value(scmd->cmd[1]) == 2)
			{
				//value = value
				new_node->value = value;
				//display flag 1
				new_node->env_display = TRUE;
				write (1, "existing val set to new value in env and export\n\n", 49);
			}
		}
		//else: if no equal sign nothing happens
	}
	//if node does not exist yet
	else
	{
		//create new node with key = key
		new_node = ft_new_env_node(key, NULL, TRUE);
		//if no equal sign
		if (equal_sign_and_value(scmd->cmd[1]) == 0)
		{
			//key = key; -> already set, no action
			//value = NULL --> alrady set, no action
			//diplay flag = FALSE;
			new_node->env_display = FALSE;
			write (1, "new empty val added only to export\n", 37);
		}
		//if equal sign and no value -> return 1
		if (equal_sign_and_value(scmd->cmd[1]) == 1)
		{
			//key = key --> already set, no action
			//value = \0
			new_node->value = '\0';
			//diplay flag 1 --> export and env --> already set
			write (1, "new empty val added to env and export\n\n", 39);
		}
		//if equal sign and value -> return 2
		else if (equal_sign_and_value(scmd->cmd[1]) == 2)
		{
			//key = key; -_> already, no action
			//value = value
			new_node->value = value;
			//display flag 1 --> export and env --> already set
			write (1, "new full val added to env and export\n\n", 38);
		}
		ft_add_last_node(&cmds->env_ll, new_node);
	}
	printf("check");
	// (free(key), free(value));
	// key = NULL;
	// value = NULL;
	//print_export(cmds->env_ll);
}
// 	else if (find_node(cmds, needle) == NULL)
// 	{
// 		write (1, "\ncheck1\n", 8);
// 		new_node = ft_new_env_node(scmd->cmd[1], NULL, FALSE);
// 		//check if there is an assignment, if there is 
// 		if (scmd->cmd[2] && ft_strncmp(scmd->cmd[2], "=\0", 2) == 0)
// 		{
// 			if (!scmd->cmd[3])
// 			{
// 				new_node->value = ft_strdup("\0");
// 				write (1, "new empty val added to env and export\n\n", 39);
// 			}
// 			else
// 			{
// 		 	  	new_node->value = ft_strdup(scmd->cmd[3]);
// 				write (1, "new full val added to env and export\n\n", 38);
// 			}
// 		 	new_node->env_display = TRUE;
// 		}
// 		else
// 			write (1, "new empty val added only to export\n", 37);
// 		ft_add_last_node(&cmds->env_ll, new_node);
// 	}
// 	//if node exists
// 	else
// 	{
// 		write (1, "\ncheck2\n", 8);
// 		new_node = find_node(cmds, scmd->cmd[1]);
// 		//check if there is an assignment
// 		if (scmd->cmd[2] && ft_strncmp(scmd->cmd[2], "=\0", 2) == 0)
// 		{
// 			if (new_node->value)
// 			 	free(new_node->value);	
// 			if (!scmd->cmd[3])
// 			{
// 				new_node->value = ft_strdup("\0");
// 				write (1, "existing val set to null in env and export\n\n", 45);
// 			}
// 			else
// 			{
// 				new_node->value = ft_strdup(scmd->cmd[3]);
// 				write (1, "existing val set to new value in env and export\n\n", 49);
// 			}
// 		}
// 	}
// 	
// 	//print_export(cmds->env_ll);
// 	//builtin_env(cmds->env_ll);
// }
