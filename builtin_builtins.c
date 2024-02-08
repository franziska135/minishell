/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 14:29:58 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//what happens on error?
void	builtin_pwd(void)
{
	char	buf[100];

	if (getcwd(buf, 100) != NULL)
	{
		write(1, buf, ft_strlen(buf));
		write (1, "\n", 1);
	}
	else
		print_error(NULL, "pwd", strerror(errno));
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

void	builtin_exit(t_compound *cmds)
{
	cleanup_envp_ll(cmds->env_ll);
	free_double_ptr(cmds->envp);
	struct_free(*cmds);
	//exit code on regular exit?
	exit (1);
}
