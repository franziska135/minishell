#include "minishell.h"

static char	*find_key(char *token)
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
	str[j] = '=';
	str[j + 1] = '\0';
	return (str);
}

static void	write_expansion(t_compound *cmds, char *token, int fd)
{
	t_env	*env;
	char	*key;

	key = find_key(token);
	if (key)
	{
		env = find_node(cmds, key);
		if (env)
			write(fd, env->value, ft_strlen(env->value));
	}
	else if (token[0] == '\0')
		write(fd, "$", 1);
	free(key);
}

static char	*expand_token(t_compound *cmds, char *token)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) == -1)
		return (NULL);
	while (token[0])
	{
		if (in_quot(token, 0) == 1 || token[0] != '$')
		{
			write(fd[1], token, 1);
			token ++;
		}
		else
		{
			token++;
			write_expansion(cmds, token, fd[1]);
			while(token[0] && (ft_isalpha(token[0]) || token[0] == '_'))
				token++;
		}
	}
	write(fd[1], "\0", 1);
	close(fd[1]);
	str = get_next_line(fd[0]);
	close(fd[0]);
	return (str);
}

char	*token_expand(t_compound *cmds, char **tokens)
{
	char	*str;
	int		i;

	i = 0;
	while (tokens[i])
	{
		str = expand_token(cmds, tokens[i]);
		if (str)
		{
			free(tokens[i]);
			tokens[i] = remove_quotes(str);
		}
		else
		{
			free(str);
			tokens[i] = (char *)malloc(sizeof(char) * 1);
			tokens[i][0] = '\0';
		}
		i++;
	}
}