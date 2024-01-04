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

int	main(void)
{
	t_path		binarypaths;
	t_compound	compound;

	compound.amt_simple_cmds = 1;
	// init_path_struct(&binarypaths);
	//splits the path if one exists, otherwise does nothing, error message later
	split_binary_paths(&binarypaths, &compound);
	process_commands(&binarypaths, &compound);
	// builtins(&m, argc, argv;
	cleanup(&binarypaths, &compound);
}

void	process_commands(t_path *binarypaths, t_compound *compound)
{
	if (compound->amt_simple_cmds == 0)
	//do sth
	if (compound->amt_simple_cmds == 1)
	//check for builtin
	if (compound->amt_simple_cmds > 1)
	//use pipe
}
