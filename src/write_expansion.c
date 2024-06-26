/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:16:36 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:16:38 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_env(t_env *env, int fd[2][2], int flag)
{
	size_t	i;

	write(fd[0][1], env->value, ft_strlen(env->value));
	i = 0;
	while (i < ft_strlen(env->value))
	{
		ft_putnbr_fd(flag, fd[1][1]);
		i++;
	}
}

static void	expand_exit_status(t_compound *cmds, int fd, int fd_flag, int flag)
{
	int	nbr;

	nbr = WEXITSTATUS(cmds->exit_status);
	if (WIFEXITED(cmds->exit_status))
	{
		ft_putnbr_fd(WEXITSTATUS(cmds->exit_status), fd);
		if (nbr == 0)
			ft_putnbr_fd(flag, fd_flag);
		while (nbr)
		{
			ft_putnbr_fd(flag, fd_flag);
			nbr /= 10;
		}
	}
	else
	{
		write (fd, "0", 1);
		ft_putnbr_fd(flag, fd_flag);
	}
}

int	write_expansion(t_compound *cmds, char *token, int fd[2][2], int flag)
{
	t_env	*env;
	char	*key;
	int		ret;

	token++;
	ret = 0;
	key = find_key(token);
	if (key)
	{
		env = find_node(cmds, key);
		ret = ft_strlen(key);
		free(key);
		if (env && env->value && env->env_display < 2)
			return (expand_env(env, fd, flag), ret);
	}
	else if (token[0] == '?')
		return (expand_exit_status(cmds, fd[0][1], fd[1][1], flag), 1);
	else if ((token[0] != '_' && token[0] != '"' && token[0] != '\''
			&& !ft_isalpha(token[0])) || flag != 0)
	{
		write(fd[0][1], "$", 1);
		ft_putnbr_fd(flag, fd[1][1]);
	}
	return (ret);
}
