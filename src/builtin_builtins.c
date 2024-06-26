/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:26 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_compound *cmds)
{
	char	buf[500];

	if (getcwd(buf, 500) != NULL)
	{
		write(1, buf, ft_strlen(buf));
		write (1, "\n", 1);
		set_status(cmds, 0);
	}
	else if (errno == 2 && cmds->pwd)
	{
		write(1, cmds->pwd, ft_strlen(cmds->pwd));
		write (1, "\n", 1);
		set_status(cmds, 0);
	}
	else
	{
		print_error(NULL, "pwd", strerror(errno));
		set_status(cmds, 2);
	}
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

void	set_status(t_compound *cmds, int i)
{
	cmds->exit_status = i << 8;
}
