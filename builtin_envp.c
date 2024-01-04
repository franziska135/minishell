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

// void	init_path_struct(t_path *binarypaths)
// {
// 	binarypaths->paths = NULL;
// 	binarypaths->paths_str = NULL;
// }

void	split_binary_paths(t_path *binarypaths, t_compound *compound)
{
	char	*path_str;

	binarypaths->paths = NULL;
	path_str = getenv("PATH");
	if (path_str != NULL)
	{
		binarypaths->paths = ft_split(path_str, ':');
		if (!binarypaths->paths)
			cleanup(binarypaths, compound);
		print_paths(binarypaths);
		free(path_str);
		path_str = NULL;
	}
}
//can be taken out later
void	print_paths(t_path *binarypaths)
{
	int	i;

	i = 0;
	while (binarypaths->paths[i] != NULL)
	{
		printf("%s\n", binarypaths->paths[i]);
		i++;
	}
}