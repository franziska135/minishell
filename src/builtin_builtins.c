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

//what happens on error?
void	builtin_pwd(t_compound *cmds)
{
	char	buf[500];

	if (getcwd(buf, 500) != NULL)
	{
		write(1, buf, ft_strlen(buf));
		write (1, "\n", 1);
		cmds->exit_status = 0;
	}
	else
	{
		print_error(NULL, "pwd", strerror(errno));
		cmds->exit_status = 2;
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

int	exit_error_check(t_compound *cmds, t_simple *scmd)
{
	int	i;

	i = 0;
	if (!scmd->cmd[1])
		return (0);
	if (scmd->cmd[1][0] == '\0')
		return (print_error("exit: ", "", "numeric argument required"), 2);
	if (scmd->cmd[1][0] == '-' || scmd->cmd[1][0] == '+')
		i++;
	while (scmd->cmd[1][i])
	{
		if (ft_isdigit(scmd->cmd[1][i]) == 0)
		{
			print_error("exit: ", scmd->cmd[1], "numeric argument required");
			return (2);
		}
		i++;
	}
	if (scmd->cmd[2])
	{
		print_error("exit: ", NULL, "too many arguments");
		return (1);
	}
	else
		return (3);
}

void	builtin_exit(t_compound *cmds, t_simple *scmd)
{
	int	status;

	status = exit_error_check(cmds, scmd);
	cmds->exit_status = status;
	cleanup_envp_ll(cmds->env_ll);
	free_double_ptr(cmds->envp);
	struct_free(*cmds);
	//exit code on regular exit?
	exit(WEXITSTATUS(status));
}
