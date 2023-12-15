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

void	builtins(t_list *m, int argc, char **argv)
{
	if (argv[1])
	{
		if (ft_strncmp(argv[1], "pwd\0", 4) == 0)
			ft_pwd(m);
		else if (ft_strncmp(argv[1], "env\0", 4) == 0)
			ft_env(m);
		else if (ft_strncmp(argv[1], "unset\0", 7) == 0)
		{
			if (argv[2])
				ft_unset(m, argv[2]);
			else
				ft_write_error(NOT_ENOUGH_ARGUMENTS, argv[1]);
		}
		else
			ft_write_error(CMD_NOT_FOUND, argv[1]);
	}
}

void	ft_pwd(t_list *m)
{
	if (find_envp_path(m, "PWD=") == 1 || find_envp_path(m, "OLDPWD=") == 1)
	{
		printf("%s\n", m->envp[m->index_path]);
		m->index_path = 0;
	}
	//on error nothing is shown (testable with unset PWD and unset OLDPWD)
}

//unset needs a parameter to be passed with it-> error check
void	ft_unset(t_list *m, char *str)
{
	int	i;
	char *tmp;

	tmp = NULL;
	if (find_envp_path(m, str) == 1)
	{
		i = m->index_path;
		free(m->envp[m->index_path]);
		m->envp[m->index_path] = NULL;
		while (m->envp[i + 1])
		{
			tmp = ft_strdup(m->envp[i + 1]);
			if (!tmp)
				cleanup(m, EXIT);
			free(m->envp[i]);
			m->envp[i] = tmp; 
			i++;
		}
		if (tmp)
			(free(tmp), tmp = NULL);
		// if (m->envp[i])
		// 	free(m->envp[i]);
	}
}

// void	ft_echo(t_list *m)
// {

// }

// void	ft_cd(t_list *m)
// {

// }

// void	ft_export(t_list *m)
// {
	
// }
void	ft_env(t_list *m)
{
	int	i;

	i = 0;
	while (m->envp[i])
	{
		printf("%s\n", m->envp[i]);
		i++;
	}
}
// void	ft_exit(t_list *m)
// {
	
// }
