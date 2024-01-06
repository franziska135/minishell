#include "minishell.h"

size_t	pipe_counter(char *str)
{
	size_t		len;
	size_t		i;
	size_t		res;

	len = ft_strlen(str);
	i = 0;
	res = 0;
	while(i < len)
	{
		if (str[i] == '|' && !in_quot(str, i))
		{
			if (i == 0 || i == len - 1)
			{
				err_handler("SYNTAX ERR");
				return (0);
			}
			else if (str[i - 1] != '>')
				res++;
		}
		i++;
	}
	return (res);
}

t_compound	parser(char *str)
{
	t_compound cmds;

	cmds.nbr_scmd = pipe_counter(str);
	printf("%zu\n", cmds.nbr_scmd);
}
