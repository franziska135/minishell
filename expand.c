/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 15:24:47 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	tokens_counter(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

char	*find_key(char *token)
{
	size_t	j;
	char	*str;

	j = 0;
	if (!token)
		return (NULL);
	if (token[0] && ft_isdigit(token[0]))
		return (NULL);
	while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
		j++;
	if (j == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (j + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, token, j + 1);
	str[j] = '\0';
	return (str);
}

static int	write_expansion(t_compound *cmds, char *token, int fd, int fd_flag, int flag)
{
	t_env	*env;
	char	*key;
	size_t	i;
	int		ret;

	token++;
	ret = 0;
	key = find_key(token);
	if (key)
	{
		env = find_node(cmds, key);
		ret = ft_strlen(key);
		free(key);
		if (env && env->value)
		{
			write(fd, env->value, ft_strlen(env->value));
			i = 0;
			while (i < ft_strlen(env->value))
			{
				ft_putnbr_fd(flag, fd_flag);
				i++;
			}
			return (ret);
		}
	}
	else if (token[0] == '?')
	{
		if (WIFEXITED(cmds->exit_status))
			ft_putnbr_fd(WEXITSTATUS(cmds->exit_status), fd);
		else
			write (fd, "0", 1);
		// check for how many digits;
		ft_putnbr_fd(flag, fd_flag);
		ret++;
	}
	else if ((token[0] != '_' && token[0] != '"' && token[0] != '\'' && !ft_isalpha(token[0])) || flag != 0)
	{
		write(fd, "$", 1);
		ft_putnbr_fd(flag, fd_flag);
	}
	return (ret);
}

int	expand_token(t_compound *cmds, char *token, int *fd, int *fd_flag)
{
	int		flag;
	int		empty;

	flag = 0;
	empty = 0;
	while (token[0])
	{
		if (token[0] == '"' && flag == 0)
			flag = 2;
		else if (token[0] == '"' && flag == 2)
			flag = 0;
		else if (token[0] == '\'' && flag == 0)
			flag = 1;
		else if (token[0] == '\'' && flag == 1)
			flag = 0;
		else if (flag == 1 || token[0] != '$')
		{
			write(fd[1], token, 1);
			ft_putnbr_fd(flag, fd_flag[1]);
			empty = 1;
		}
		else
		{
			token += (write_expansion(cmds, token, fd[1], fd_flag[1], flag));
			empty = 1;
		}
		token++;
	}
	if (empty == 0)
		return (3);
	return (0);
}


char	**expand_redir(t_compound *cmds, char *token)
{
	char	*str;
	char	*flag;
	int		fd[2];
	int		fd_flag[2];
	char	**split;

	if (pipe(fd) == -1)
		return (NULL);
	if (pipe(fd_flag) == -1)
		return (close(fd[1]), close(fd[0]),NULL);
	expand_token(cmds, token, fd, fd_flag);
	write(fd[1], "\0", 1);
	write(fd_flag[1], "\0", 1);
	close(fd[1]);
	close(fd_flag[1]);
	str = get_next_line(fd[0]);
	close(fd[0]);
	if (!str || str[0] == '\0')
		return (close(fd_flag[0]), close(fd_flag[1]), free(str), NULL);
	flag = get_next_line(fd_flag[0]);
	close(fd_flag[0]);
	if (!flag)
		return (free(str), NULL);
	split = expansion_split(str, flag);
	free(flag);
	free(str);
	if (!split)
		return(NULL);
	if (!split[0] || split[1])
	{
		dpointer_free(split);
		return (NULL);
	}
	return (split);
}