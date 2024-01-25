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
		if (current->value)
		{
			write (1, "=", 1);
			//printf("%s", current->value);
			write(1, current->value, ft_strlen(current->value));
		}
		write (1, "\n", 1);
		current = current->next;
	}
	//take out
	write (2, "-------EXPORT END-------------\n", 31);
	//newline at the end?
}

void	builtin_export(t_compound *cmds, t_simple *scmd)
{
	int		i;
	t_env	*new_node;

	i = 0;
	if (!scmd->cmd[1])
		print_export(cmds->env_ll);
	else if (ft_strncmp(scmd->cmd[1], "=\0", 2) == 0)
		print_error("minishell: ", "export: ", "'='", "not a valid identifier");
	//create node if variable does not exist yet
	else if (find_node(cmds, scmd->cmd[1]) == NULL)
	{
		write (1, "\ncheck1\n", 8);
		new_node = ft_new_env_node(scmd->cmd[1], NULL, FALSE);
		//check if there is an assignment, if there is 
		if (scmd->cmd[2] && ft_strncmp(scmd->cmd[2], "=\0", 2) == 0)
		{
			if (!scmd->cmd[3])
			{
				new_node->value = ft_strdup("\0");
				write (1, "new empty val added to env and export\n\n", 39);
			}
			else
			{
		 	  	new_node->value = ft_strdup(scmd->cmd[3]);
				write (1, "new full val added to env and export\n\n", 38);
			}
		 	new_node->env_display = TRUE;
		}
		else
			write (1, "new empty val added only to export\n", 39);
		ft_add_last_node(&cmds->env_ll, new_node);
	}
	//if node exists
	else
	{
		write (1, "\ncheck2\n", 8);
		new_node = find_node(cmds, scmd->cmd[1]);
		//check if there is an assignment
		if (scmd->cmd[2] && ft_strncmp(scmd->cmd[2], "=\0", 2) == 0)
		{
			if (new_node->value)
			 	free(new_node->value);	
			if (!scmd->cmd[3])
			{
				new_node->value = ft_strdup("\0");
				write (1, "existing val set to null in env and export\n\n", 45);
			}
			else
			{
				new_node->value = ft_strdup(scmd->cmd[3]);
				write (1, "existing val set to new value in env and export\n\n", 49);
			}
		}
	}
	//print_export(cmds->env_ll);
	//builtin_env(cmds->env_ll);
}
