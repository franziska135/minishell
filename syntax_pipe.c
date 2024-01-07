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

int	syntax_pipe(char *str)
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