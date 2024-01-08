#include "minishell.h"


static int	pipe_argument(char *str, int i)
{
	i++;
	while (i < ft_strlen(str) && str[i] != '|')
	{
		if (ft_isprint(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

static int	syntax_pipe(char *str)
{
	size_t	i;
	int		printable;

	i = 0;
	printable = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '|')
		{
			if (printable == 0)
				return (1);
			if (!in_quot(str, i) && !pipe_argument(str, i))
				return (1);			
		}
		if (printable == 0 && ft_isprint(str[i]) && str[i] != ' ' && str[i] != '\t')
			printable = 1;
		i++;
	}
	return (0);
}
static int	redir_argument(char *str, int i)
{
	i++;
	if (str[i - 1] == '>' && (str[i] == '>' || str[i] == '|'))
		i++;
	else if (str[i - 1] == '<' && str[i] == '<')
		i++;	
	while (i < ft_strlen(str) && str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		if (ft_isprint(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

static int	syntax_redir(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (!in_quot(str, i) && !redir_argument(str, i))
				return (1);			
		}
		i++;
	}
	return (0);
}

int	syntax(char *str)
{
	if (in_quot(str, ft_strlen(str) - 1))
	{
		err_handler("SYNTAX ERROR (quotes)");
		return (0);
	}
	if (syntax_pipe(str))
	{
		err_handler("SYNTAX ERROR (pipe)");
		return (0);
	}
	if (syntax_redir(str))
	{
		err_handler("SYNTAX ERROR (redirection)");
		return (0);
	}
	printf ("\n***NO ERROR***\n");
	return (1);
}