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

int	expand_token(t_compound *cmds, char *token, int fd[2][2])
{
	int		flag;
	int		e;

	flag = 0;
	e = 3;
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
			(write(fd[0][1], token, 1), ft_putnbr_fd(flag, fd[1][1]), e = 0);
		else
		{
			token += (write_expansion(cmds, token, fd, flag));
			e = 0;
		}
		token++;
	}
	return (e);
}

static int	close_n_read(char **str, char **flag, int fd[2][2])
{
	write(fd[0][1], "\0", 1);
	write(fd[1][1], "\0", 1);
	close(fd[0][1]);
	close(fd[1][1]);
	*str = get_next_line(fd[0][0]);
	close(fd[0][0]);
	if (!*str || *str[0] == '\0')
		return (close(fd[1][0]), free(*str), 0);
	*flag = get_next_line(fd[1][0]);
	close(fd[1][0]);
	if (!*flag)
		return (free(*str), 0);
	return (1);
}

char	**expand_redir(t_compound *cmds, char *token)
{
	char	*str;
	char	*flag;
	int		fd[2][2];
	char	**split;

	if (pipe(fd[0]) == -1)
		return (NULL);
	if (pipe(fd[1]) == -1)
		return (close(fd[0][1]), close(fd[0][0]), NULL);
	expand_token(cmds, token, fd);
	if (!close_n_read(&str, &flag, fd))
		return (NULL);
	split = expansion_split(str, flag);
	free(flag);
	free(str);
	if (!split)
		return (NULL);
	if (!split[0] || split[1])
	{
		dpointer_free(split);
		return (NULL);
	}
	return (split);
}
