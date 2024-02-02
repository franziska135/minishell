#include "minishell.h"

static size_t	malloc_size(char **tokens, int i)
{
	size_t	len;
	int		j;
	int		status;

	len = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			return (len);
		else if (tokens[i][0] == '>' || tokens[i][0] == '<')
			i++;
		else
		{
			j = 0;
			status = 0;
			while (tokens[i][j])
			{
				if (!status && tokens[i][j] != ' ')
				{
					len ++;
					status = 1;
				}
				else if (tokens[i][j] == ' ')
					status = 0;
				j++;
			}
		}
		i++;
	}
	return (len);
}


static int	malloc_struct(t_compound *cmds, char **tokens)
{
	size_t	i;
	size_t	len;
	int		pipe;

	i = 0;
	pipe = 0;
	len = 0;
	while (tokens[i])
	{
		len = malloc_size(tokens, i);
		cmds->scmd[pipe].cmd = (char **)malloc(sizeof(char *) * (len + 1));
		if (!cmds->scmd[pipe].cmd)
			return(struct_free(*cmds), dpointer_free(tokens), 0);
		cmds->scmd[pipe].cmd[len] = NULL;
		while (tokens[i + 1] && tokens[i][0] != '|')
			i++;
		pipe++;
		i++;
	}
	return (1);
}

static int	write_struct(t_compound *cmds, char **tokens)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	pipe;
	char	**str;

	i = 0;
	j = 0;
	pipe = 0;
	while(tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			pipe++;
			j = 0;
		}
		else if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i++;
		else
		{
			str = ft_split(tokens[i], ' ');
			if (!str)
				return (struct_free(*cmds), 0);
			k = 0;
			while (str[k])
			{
				cmds->scmd[pipe].cmd[j + k] = (char *)malloc(sizeof(char) * (ft_strlen(tokens[i]) + 1));
				if(!cmds->scmd[pipe].cmd[j + k])
					return(struct_free(*cmds), dpointer_free(tokens), 0);
				ft_strlcpy(cmds->scmd[pipe].cmd[j + k], str[k], ft_strlen(str[k]) + 1);
				k++;
			}
			j++;
			dpointer_free(str);
		}
		i++;
	}
	return (1);
}

int	struct_cpy(t_compound *cmds, char **tokens)
{
	if(!malloc_struct(cmds, tokens))
	{
		dpointer_free(tokens);
		return (0);
	}
	if (!write_struct(cmds, tokens))
	{
		struct_free(*cmds);
		dpointer_free(tokens);
		return (0);
	}
	return (1);
}
