#include "minishell.h"

static int	all_space(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}


static int	run_procces(t_compound	*cmds, char *str)
{
	char	**tokens;
	
	if (!syntax(str))
		return (free(str), 0);
	tokens = lexis(str);
	if (!tokens)
		return (free(str), 0);
	if(!parser(cmds, tokens))
		return (0);
	print_struct(*cmds);
	dpointer_free(tokens);
	struct_free(*cmds);
	return (1);
}

int	run_minishell(t_compound	*cmds)
{
	HIST_ENTRY	**history_list;
	char		*str;
	int			i;

	while(TRUE)
	{
		str = readline("fzsh: ");
		if (!all_space(str))
		{
			if (str[0] != ' ')
				add_history(str);
			run_procces(cmds, str);
		}
	}
	return (0);
}

