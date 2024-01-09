#include "minishell.h"

static size_t	malloc_size(char **tokens, int i)
{
	size_t	len;

	len = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			return (len);
		else if (!ft_strncmp(tokens[i], ">", 2) || !ft_strncmp(tokens[i], "<", 2)
				|| !ft_strncmp(tokens[i], ">>", 3))
			i++;
		else
			len++;
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
	size_t	pipe;

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
			cmds->scmd[pipe].cmd[j] = (char *)malloc(sizeof(char) * (ft_strlen(tokens[i]) + 1));
			ft_strlcpy(cmds->scmd[pipe].cmd[j], tokens[i], ft_strlen(tokens[i]) + 1);
			if(!cmds->scmd[pipe].cmd)
				return(struct_free(*cmds), dpointer_free(tokens), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	struct_cpy(t_compound *cmds, char **tokens)
{
	if(!malloc_struct(cmds, tokens))
		return (0);
	if (!write_struct(cmds, tokens))
		return (0);
	return (1);
}
