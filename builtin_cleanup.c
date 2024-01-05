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

void	cleanup(t_list *execute, t_compound *compound)
{
	if (execute)
	{
		if (execute->binary_paths)
			free_double_ptr(execute->binary_paths);
	}
	// if (compound)
	// {
	// 	if (compound->cmd)
	// 		free_list(compound->cmd);
	// 	if (compound->cmd_line)
	// 		(free(compound->cmd_line), compound->cmd_line = NULL);
	// }
	//no exit
}

//may need adjustments if struct changes
// void	free_list(t_simple **cmd)
// {
// 	int	i;
// 	int	j;
// 	int	z;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		j = 0;
// 		z = 0;
// 		if (cmd[i]->command)
// 			free_double_ptr(cmd[i]->command);
// 		if (cmd[i]->hd_delimiter)
// 			free_double_ptr(cmd[i]->hd_delimiter);
// 		if (cmd[i]->outfile)
// 			(free(cmd[i]->outfile), cmd[i]->outfile = NULL);
// 		if (cmd[i]->infile)
// 			(free(cmd[i]->infile), cmd[i]->infile = NULL);
// 		if (cmd[i]->append)
// 			(free(cmd[i]->append), cmd[i]->append = NULL);

// 		i++;
// 	}
// }

void	free_double_ptr(char **double_ptr)
{
	int	i;

	i = 0;
	while (double_ptr[i])
	{
		free(double_ptr[i]);
		i++;
	}
	double_ptr = NULL;
}

// void	ft_write_error(int status, char *str)
// {

// 	if (status == CANT_OPEN)
// 	{
// 		write(2, "minishell: ", 11);
// 		write(2, "no such file or directory: ", 28);
// 		write(2, str, ft_strlen(str));
// 	}
// 	else if (status == NOT_ENOUGH_ARGUMENTS)
// 	{
// 		write(2, str, ft_strlen(str));
// 		write(2, ": not enough arguments", 22);
// 	}
// 	else if (status == CMD_NOT_FOUND)
// 	{
// 		write(2, "minishell: ", 11);
// 		write(2, "command not found: ", 19);
// 		write(2, str, ft_strlen(str));
// 	}
// 	write(2, "\n", 1);
// }
