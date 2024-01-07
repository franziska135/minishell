#include "minishell.h"

int	is_delimiter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t')
		return (TRUE);
	return(FALSE);
}

int	in_quot(char *str, size_t n)
{
	size_t	i;
	size_t	j;
	int		res;

	i = 0;
	res = 0;
	while(str && str[i] && i <= n)
	{
		if (str[i] == '\'' && res != 2)
		{
			if (res == 1)
				res = 0;
			else
				res = 1;
		}
		if (str[i] == '"' && res != 1)
		{
			if (res == 2)
				res = 0;
			else
				res = 2;
		}
		i++;
	}
	return (res);
}
