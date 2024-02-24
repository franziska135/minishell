/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 16:56:30 by mzolfagh         ###   ########.fr       */
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

static void	print_eof_hd(char *delim, int *fd)
{
	write (2, "\nfzsh: warning: here-document at ", 34);
	write (2, "line 1 delimited by end-of-file (wanted `", 42);
	write (2, delim, ft_strlen(delim));
	write (2,"')\n", 4);
}

int	ft_here_doc(char *delimiter, t_compound *cmds, int expand)
{
	int		fd[2];
	char	*gnl;

	if (pipe(fd) == -1)
		return (-1);
	// write (1, "> ", 3);
	gnl = get_next_line(STDIN_FILENO);
	if (gnl && gnl[ft_strlen(gnl) - 1] == '\n')
		gnl[ft_strlen(gnl) - 1] = '\0';
	if (!gnl && errno != ENOMEM)
		print_eof_hd(delimiter, fd);
	while (gnl && ft_strncmp(delimiter, gnl, ft_strlen(gnl) + 1) != 0 && g_signal != -1)
	{
		expand_hd(gnl, cmds, fd[1], expand);
		free(gnl);
		// write (1, "> ", 3);
		gnl = get_next_line(STDIN_FILENO);
		if (!gnl && errno != ENOMEM)
		{
			print_eof_hd(delimiter, fd);
			break;
		}
		if (gnl && gnl[ft_strlen(gnl) - 1] == '\n' && g_signal != -1)
			gnl[ft_strlen(gnl) - 1] = '\0';
	}
	free(gnl);
	if (g_signal == -1)
	{
		close (fd[0]);
		fd[0] = -1;
	}
	close (fd[1]);
	
	return (fd[0]);
}
