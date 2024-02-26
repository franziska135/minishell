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

	i = -1;
	if (!scmd->cmd[1])
		return (0);
	if (scmd->cmd[1][0] == '\0')
		return (print_error("exit: ", "", "numeric argument required"), 2);
	if (scmd->cmd[1][0] == '-' || scmd->cmd[1][0] == '+')
		i++;
	while (scmd->cmd[1][++i])
	{
		if (ft_isdigit(scmd->cmd[1][i]) == 0)
		{
			print_error("exit: ", scmd->cmd[1], "numeric argument required");
			return (2);
		}
	}
	if (scmd->cmd[2])
	{
		print_error("exit: ", NULL, "too many arguments");
		set_status(cmds, 1);
		return (1);
	}
	else
		return (normalize_exit_code(ft_atoi(scmd->cmd[1])));
}

void	builtin_exit(t_compound *cmds, t_simple *scmd, int initial_stdout)
{
	int	status;

	status = exit_error_check(cmds, scmd);
	cleanup_envp_ll(cmds->env_ll);
	free_double_ptr(cmds->envp);
	struct_free(*cmds);
	if (initial_stdout != -1)
		close(initial_stdout);
	exit(status);
}
