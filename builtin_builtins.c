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

//what happens on error?
void	builtin_pwd(void)
{
	char	buf[100];

	if (getcwd(buf, 100) != NULL)
		write(1, buf, ft_strlen(buf));
	write (1, "\n", 1);
}

//takes the head of the env_ll as argument and iterates through all nodes, printing their content
void builtin_env(t_env *head)
{
	t_env *current;
	
	current = head;

	//take out:
	write(1, "\n", 1);
	write (2, "-------ENV START-------------\n", 30);
	while (current)
	{
		if (current->env_display == TRUE)
		{
			write(1, current->key, ft_strlen(current->key));
			write (1, "=", 1);
			if (current->value)
				write(1, current->value, ft_strlen(current->value));
			write (1, "\n", 1);
		}
		current = current->next;
	}
	//take out
	write (2, "-------ENV END-------------\n", 28);
	//newline at the end?
}

void	print_error(char *str2, char *str3, char *str4)
{
	write (2, "fzsh: ", 6);
	if (str2)
		write (2, str2, ft_strlen(str2));
	if (str3)
	{
		write (2, str3, ft_strlen(str3));
		write (2, ": ", 2);
	}
	if (str4)
		write (2, str4, ft_strlen(str4));
	write (2, "\n", 1);
}

/*Unsetting a variable or function that was not previously set
shall not be considered an error and does not cause the shell to
abort.*/

void	builtin_unset(t_compound *cmds, t_simple *scmd)
{
	t_env	*haystack;
	t_env	*tmp;
	char	*needle;

	needle = NULL;
	if (scmd->cmd[1])
		needle = scmd->cmd[1];
	haystack = cmds->env_ll;
	if (needle)
	{
		while (haystack)
		{
			if (ft_strncmp(haystack->key, needle, ft_strlen(haystack->key)) == 0)
			{
					tmp->next = haystack->next;
					haystack->next = NULL;
					write(1, haystack->key, ft_strlen(haystack->key));
					write (1, " is now unset\n", 14);
					ft_free_list(haystack);
					return ;
			}
			tmp = haystack;
			haystack = haystack->next;
		}
		write (1, "variable not found\n", 19);
	}
}

void	builtin_exit(t_compound *cmds)
{
	cleanup_envp_ll(cmds->env_ll);
	free_double_ptr(cmds->envp);
	struct_free(*cmds);
	exit (1);
}
