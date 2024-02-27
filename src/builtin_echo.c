/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:02 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_compound *cmds, t_simple *scmd)
{
	int	i;
	int	start;

	i = 0;
	set_status(cmds, 0);
	if (scmd->cmd[1])
	{
		i = check_for_n(scmd);
		if (check_for_only_n(scmd->cmd[i]) == TRUE)
			builtin_echo_write(cmds, scmd, i);
		else
		{
			builtin_echo_write(cmds, scmd, 0);
			write (1, "\n", 1);
		}
	}
	else
		write (1, "\n", 1);
}

void	if_echo_home(t_compound *cmds)
{
	t_env	*home;

	home = find_node(cmds, "HOME");
	if (home != NULL && home->value != NULL)
	{
		write (1, home->value, ft_strlen(home->value));
	}
	else
		set_status(cmds, 1);
}

void	builtin_echo_write(t_compound *cmds, t_simple *scmd, int i)
{
	if (scmd->cmd[i + 1])
	{
		if (ft_strncmp(scmd->cmd[i + 1], "~", 2) == 0)
			if_echo_home(cmds);
		else
			write (1, scmd->cmd[i + 1], ft_strlen(scmd->cmd[i + 1]));
		while (scmd->cmd[++i + 1])
		{
			write (1, " ", 1);
			if (ft_strncmp(scmd->cmd[i + 1], "~", 2) == 0)
				if_echo_home(cmds);
			else
				write (1, scmd->cmd[i + 1], ft_strlen(scmd->cmd[i + 1]));
		}
	}
}

//utils functions for builtin_echo, checks every cmd if valid -n
//returns the index of the last occurence of a valid -n arg
//or if none exist: returns index of string to be printed
int	check_for_n(t_simple *scmd)
{
	int		i;
	int		index_last_only_n;

	i = 1;
	index_last_only_n = 1;
	while (scmd->cmd[i] && check_for_only_n(scmd->cmd[i]) == TRUE)
	{
		index_last_only_n = i;
		i++;
	}
	return (index_last_only_n);
}

//utils function for builtin_echo
//checks if string contains only valid -n
int	check_for_only_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0' && i != 0)
		return (TRUE);
	else
		return (FALSE);
}
