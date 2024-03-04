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

	i = 0;
	if (scmd->cmd[1][0] == '-' || scmd->cmd[1][0] == '+')
		i++;
	if (scmd->cmd[1][i] == '\0')
	return (FALSE);
	while (scmd->cmd[1][i])
	{
		if (ft_isdigit(scmd->cmd[1][i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	long_max(t_simple *scmd)
{
	long int	max_long;
	char		*number;
	char		*doublicate;
	int			i;
	int			j;

	max_long = ft_atoi(scmd->cmd[1]);
	number = ft_itoa(max_long);
	i = 0;
	j = 0;
	doublicate = ft_strdup(scmd->cmd[1]);
	if (doublicate)
	{
		if (doublicate[i] == '+')
			i++;
		while (doublicate[i] && doublicate[i] == '0')
			i++;
		if (doublicate[i] == '\0')
		return (free(doublicate), free(number), TRUE);
		while (doublicate[i + j] != '\0' || number[j] != '\0')
		{
			if (doublicate[i + j] != number[j])
				return (free(doublicate), free(number), FALSE);
			j++;
		}
	}
	free(number);
	free(doublicate);
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
	else if (is_digit(scmd) == FALSE || long_max(scmd) == FALSE)
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
	if (too_many_arg(scmd) == FALSE && is_digit(scmd) == TRUE
		&& long_max (scmd) == TRUE)
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
