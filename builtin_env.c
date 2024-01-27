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

void	init_path_struct(t_execute *execute)
{
	execute->binary_paths = NULL;
}

//returns a pointer to the node storing the key and the variable
//returns NULL if key not found
t_env	*find_node(t_compound *cmds, char *needle)
{
	t_env	*haystack;
	char	*str;
	size_t	h_length;

	h_length = 0;
	haystack = cmds->env_ll;
	while (haystack)
	{
		h_length = ft_strlen(haystack->key);
		if (ft_strncmp(haystack->key, needle, ft_strlen(needle)) == 0)
			return (haystack);
		haystack = haystack->next;
	}
	return (NULL);
}

//make sure that nothing gets updated in case the variable doesnt exist
//check for if new value == NULL;
////!!!!!CHECK FOR NEW VALUIE == NULL;
//error if node is unset and not found?
void	update_env_ll(t_compound *cmds, char *variable, char *new_value)
{
	t_env	*node;


	if (new_value && variable)
	{
		node = find_node(cmds, variable);
  		if (node)
		{
    		// printf("old value of %s: \t%s\n", variable, node->value);
			free(node->value);
			node->value = ft_strdup(new_value);
			// printf("new  value of %s: \t%s\n\n", variable, node->value);
		}
	}
}

//splits the path under PATH=to check 
void	split_binary_paths(t_execute *execute, t_compound *cmds)
{
	t_env	*node;

	node = find_node(cmds, "PATH");
	if (node && node->value != NULL)
		execute->binary_paths = ft_split(node->value, ':');
	else
		printf("no path found\n");
	// if (!execute->binary_paths)
		// (free (path_str), path_str = NULL);
		// 	free everything for the current process, return to history readline;
	// print_paths(execute);
}

//can be taken out later
void	print_paths(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute->binary_paths[i] != NULL)
	{
		printf("%s\n", execute->binary_paths[i]);
		i++;
	}
}
