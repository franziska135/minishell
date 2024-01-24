#include "minishell.h"

static size_t	tokens_counter(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

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
	else if(token[0] == '?')
		ft_putnbr_fd(WEXITSTATUS(cmds->exit_status), fd);
	free(key);
}

static char	*expand_token(t_compound *cmds, char *token)
{
	char	*str;
	char	*token_copy;
	int		fd[2];
	size_t	i;

	token_copy = token;
	if (pipe(fd) == -1)
		return (NULL);
	i = 0;
	while (token[0])
	{
		if (in_quot(token_copy, i) == 1 || token[0] != '$')
		{
			write(fd[1], token, 1);
			token ++;
			i++;
		}
		else
		{
			i++;
			token++;
			write_expansion(cmds, token, fd[1]);
			if (token[0] && (ft_isdigit(token[0]) || token[0] == '?'))
			{
				i++;	
				token++;			
			}
			else
			{
				while(token[0] && (ft_isalnum(token[0]) || token[0] == '_'))
				{
					i++;	
					token++;
				}
			}
		}
	}
	write(fd[1], "\0", 1);
	close(fd[1]);
	str = get_next_line(fd[0]);
	close(fd[0]);
	return (str);
}

char	**token_expand(t_compound *cmds, char **tokens)
{
	char	**new_token;
	char	*str;
	size_t	len;
	int		i;
	int		j;

	len = tokens_counter(tokens);
	new_token = (char**)malloc(sizeof(char**) * (len + 1));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		str = expand_token(cmds, tokens[i]);
		if (str)
		{
			new_token[j] = remove_quotes(str);
			j++;
		}
		free(tokens[i]);
		i++;
	}
	free(tokens);
	new_token[j] = NULL;
	return(new_token);
}
