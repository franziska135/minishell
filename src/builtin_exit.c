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

int	normalize_exit_code(int number)
{
	return (number % 256);
}

int	exit_error_check(t_compound *cmds, t_simple *scmd)
{
	int	i;

	i = 0;
	if (!scmd->cmd[1])
		return (set_status(cmds, 0), 0);
	if (scmd->cmd[1][0] == '\0')
	{
		set_status(cmds, 2);
		return (print_error("exit: ", "", "numeric argument required"), 2);
	}
	if (scmd->cmd[1][0] == '-' || scmd->cmd[1][0] == '+')
		i++;
	if (is_digit_within_long_max(cmds, scmd, i) == FALSE)
		return (set_status(cmds, 2), 2);
	return (normalize_exit_code(ft_atoi(scmd->cmd[1])));
}

int	is_digit_within_long_max(t_compound *cmds, t_simple *scmd, int i)
{
	while (scmd->cmd[1][i])
	{
		if (ft_isdigit(scmd->cmd[1][i]) == 0)
		{
			print_error("exit: ", scmd->cmd[1], "numeric argument required");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	too_many_arg(t_compound *cmds, t_simple *scmd)
{
	if (scmd->cmd[1] && scmd->cmd[2])
	{
		print_error("exit: ", NULL, "too many arguments");
		set_status(cmds, 1);
		return (FALSE);
	}
	return (TRUE);
}

int	builtin_exit(t_compound *cmds, t_simple *scmd, int initial_stdout)
{
	int	status;

	write (1, "exit\n", 6);
	if (too_many_arg(cmds, scmd) == FALSE)
		return (cmds->exit_status);
	status = exit_error_check(cmds, scmd);
	cleanup_envp_ll(cmds->env_ll);
	free_double_ptr(cmds->envp);
	struct_free(*cmds);
	if (initial_stdout != -1)
		close(initial_stdout);
	exit(status);
}
