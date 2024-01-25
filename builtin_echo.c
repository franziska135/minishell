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

//if one -n before string argument: no newline
//infinite amt of -n possible
//once anything not following the structure -nnn... is found: string printed

void	builtin_echo(t_simple *scmd)
{
	int	i;
	int	start;

	i = 0;
	if (scmd->cmd[1])
	{
		//returns the index to the last occurence of only -n if there are any
		i = check_for_n(scmd);
		if (check_for_only_n(scmd->cmd[i]) == TRUE)
			//write i + 1, space after each word except the last
			builtin_echo_write(scmd, i);
		else
		{
			//write i, space after each word except last
			builtin_echo_write(scmd, 0);
			write (1, "\n", 1);
		}
	}
	else
		write (1, "\n", 1);
}

//utils function for echo, cuts 25 lines
void	builtin_echo_write(t_simple *scmd, int i)
{
	if (scmd->cmd[i + 1])
	{
		write (1, scmd->cmd[i + 1], ft_strlen(scmd->cmd[i + 1]));
		while (scmd->cmd[++i + 1])
		{
			write (1, " ", 1);
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
int		check_for_only_n(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}