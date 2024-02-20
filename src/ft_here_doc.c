/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2023/11/27 16:12:30 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_exit_status(int e_status, int fd)
{
	int	nbr;
	int	ret;

	nbr = WEXITSTATUS(e_status);
	ret = 0;
	if (WIFEXITED(e_status))
	{
		ft_putnbr_fd(nbr, fd);
		while (nbr)
		{
			nbr /= 10;
			ret++;
		}
	}
	else
	{
		write (fd, "0", 1);
		return (1);
	}
	return (ret);
}

static int	write_hd_expansion(t_compound *cmds, char *str, int fd)
{
	t_env	*env;
	char	*key;
	size_t	i;
	int		ret;

	str++;
	ret = 0;
	key = find_key(str);
	if (key)
	{
		env = find_node(cmds, key);
		ret = ft_strlen(key);
		free(key);
		if (env && env->value)
		{
			write(fd, env->value, ft_strlen(env->value));
			return (ret);
		}
	}
	else if (str[0] == '?')
		ret += write_exit_status(cmds->exit_status, fd);
	else if (str[0] == '\0' || str[0] == '_' || ft_isalpha(str[0]))
		write(fd, "$", 1);
	return (ret);
}

static void	expand_hd(char *str, t_compound *cmds, int fd, int expand)
{
	if (expand)
	{
		while (str && *str)
		{
			if (*str != '$')
			{
				write (fd, str, 1);
				str++;
			}
			else
				str += (write_hd_expansion(cmds, str, fd) + 1);
		}
	}
	else
		write (fd, str, ft_strlen(str));
	write (fd, "\n", 1);
}

int	ft_here_doc(char *delimiter, t_compound *cmds, int expand)
{
	int		fd[2];
	char	*gnl;

	if (pipe(fd) == -1)
		return (-1);
	gnl = get_next_line(STDIN_FILENO);
	if (gnl && gnl[ft_strlen(gnl) - 1] == '\n')
		gnl[ft_strlen(gnl) - 1] = '\0';
	while (gnl && ft_strncmp(delimiter, gnl, ft_strlen(gnl) + 1) != 0)
	{
		expand_hd(gnl, cmds, fd[1], expand);
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
		if (gnl && gnl[ft_strlen(gnl) - 1] == '\n')
			gnl[ft_strlen(gnl) - 1] = '\0';
	}
	free(gnl);
	close (fd[1]);
	return (fd[0]);
}