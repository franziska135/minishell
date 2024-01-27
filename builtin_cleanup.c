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

void	cleanup(t_execute *execute, t_compound *cmds)
{
	int	i;

	i = 0;
	// if (execute)
	// {
	// 	if (execute->binary_paths)
	// 		free_double_ptr(execute->binary_paths);
	// 	free(execute);
	// 	execute = NULL;
	// }
	// if (cmds)
	// {
	// 	if (cmds->envp)
	// 		free_double_ptr(cmds->envp);
	// 	if (cmds->env_ll)
	// 		ft_free_list(cmds->env_ll);
	// 	if (cmds->scmd)
	// 	{
	// 		while (i < cmds->nbr_scmd)
	// 		{
	// 			free_double_ptr(cmds->scmd[i].cmd);
	// 			i++;
	// 		}
	// 		free(cmds->scmd);
	// 		cmds->scmd = NULL;
	// 	}
	// }
}

//receives the head and cleans the envp linked list, valgrind checked out
void cleanup_envp_ll(t_env *env_ll)
{
	t_env *temp;

    while (env_ll != NULL)
    {
        temp = env_ll;
        env_ll = env_ll->next;
		if (temp->key)
			(free(temp->key), temp->key = NULL);
        if (temp->value)
			(free(temp->value), temp->value = NULL);
		free(temp);
    }
}

void	ft_free_list(t_env *lst)
{
	t_env	*tmp;

	if (lst)
	{
		while (lst)
		{
			tmp = (lst)->next;
			free(lst->key);
			free(lst->value);
			free(lst->next);
			free(lst);
			lst = tmp;
		}
	}
	lst = NULL;
}

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
