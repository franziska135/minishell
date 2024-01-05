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

void	init_path_struct(t_list *execute)
{
	execute->binary_paths = NULL;
	execute->amt_children = 0;
	execute->amt_pipes = 0;
}

void	split_binary_paths(t_list *execute, t_compound *compound)
{
	char	*path_str;

	
	path_str = getenv("PATH");
	if (path_str != NULL)
	{
		execute->binary_paths = ft_split(path_str, ':');
		if (!execute->binary_paths)
			cleanup(execute, compound);
		//no free of pathstr because it's a pointer to the env
		path_str = NULL;
	}
}

//can be taken out later
void	print_paths(t_list *execute)
{
	int	i;

	i = 0;
	while (execute->binary_paths[i] != NULL)
	{
		printf("%s\n", execute->binary_paths[i]);
		i++;
	}
	write (1, "\n", 1);
}
