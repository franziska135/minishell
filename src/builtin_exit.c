/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:26 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_digit(t_simple *scmd)
{
	int			i;
	long int	max_long;
	char		*number;

	i = 0;
	if (scmd->cmd[1][0] == '-' || scmd->cmd[1][0] == '+')
		i++;
	while (scmd->cmd[1][i])
	{
		if (ft_isdigit(scmd->cmd[1][i]) == FALSE)
			return (FALSE);
		i++;
	}
	max_long = ft_atoi(scmd->cmd[1]);
	number = ft_itoa(max_long);
	if (ft_strncmp(scmd->cmd[1], number, 21) != 0)
		return (free(number), FALSE);
	free(number);
	return (TRUE);
}

int	normalize_exit_code(int number)
{
	return (number % 256);
}

int	exit_error_check(t_compound *cmds, t_simple *scmd)
{
	if (!scmd->cmd[1])
		return (set_status(cmds, 0), 0);
	if (scmd->cmd[1][0] == '\0')
	{
		set_status(cmds, 2);
		return (print_error("exit: ", "", "numeric argument required"), 2);
	}
	else if (is_digit(scmd) == FALSE)
	{
		print_error("exit: ", scmd->cmd[1], "numeric argument required");
		return (set_status(cmds, 2), 2);
	}
	return (normalize_exit_code(ft_atoi(scmd->cmd[1])));
}

int	too_many_arg(t_simple *scmd)
{
	if (scmd->cmd[1] && scmd->cmd[2])
	{
		return (FALSE);
	}
	return (TRUE);
}

int	builtin_exit(t_compound *cmds, t_simple *scmd, int fdout, int fd[2])
{
	int	status;

	write (1, "exit\n", 6);
	if (too_many_arg(scmd) == FALSE && is_digit(scmd) == TRUE)
	{
		print_error("exit: ", NULL, "too many arguments");
		return (set_status(cmds, 1), cmds->exit_status);
	}
	status = exit_error_check(cmds, scmd);
	if (cmds->pwd)
		(free(cmds->pwd), cmds->pwd = NULL);
	cleanup_envp_ll(cmds->env_ll);
	free_double_ptr(cmds->envp);
	struct_free(*cmds);
	if (fdout != -1)
		close(fdout);
	if (fd != NULL)
	{
		close (fd[0]);
		close (fd[1]);
	}
	exit(status);
}
