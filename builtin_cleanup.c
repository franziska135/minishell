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
			if (lst->key)
				(free(lst->key), lst->key = NULL);
			if (lst->value)
				(free(lst->value), lst->value = NULL);
			if (lst->next)
				(free(lst->next), lst->next = NULL);
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
	if (double_ptr)
	{
		while (double_ptr[i])
		{
			free(double_ptr[i]);
			i++;
		}
		free(double_ptr);
		double_ptr = NULL;
	}
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
