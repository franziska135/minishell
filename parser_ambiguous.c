#include "minishell.h"

void	ambiguous (t_compound *cmds, char **tokens)
{
	size_t	i;
	int		pipe;
	char	*str;

	i = 0;
	pipe = 0;
	while (tokens[i])
	{
		if (tokens[i + 1])
		{
			str = expand_token(cmds, tokens[i + 1]);
			if (!ft_strncmp(tokens[i], "|", 2))
				pipe++;
			else if (!ft_strncmp(tokens[i], ">", 2) && !str)
			{
				cmds->scmd[pipe].out_fd = -1;
				print_error(NULL, tokens[i + 1], "ambiguous redirect");
			}
			else if (!ft_strncmp(tokens[i], "<", 2) && !str)
			{
				cmds->scmd[pipe].in_fd = -1;
				print_error(NULL, tokens[i + 1], "ambiguous redirect");
			}
			else if (!ft_strncmp(tokens[i], ">>", 3) && !str)
			{
				cmds->scmd[pipe].out_fd = -1;
				print_error(NULL, tokens[i + 1], "ambiguous redirect");
			}
			free(str);
		}
		i++;
	}
}
