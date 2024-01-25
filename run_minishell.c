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
		return (0);
	tokens = parser(cmds, tokens);
	if(!tokens)
		return (0);
	dpointer_free(tokens);
	if (!piping_root(cmds))
		return (0);
	struct_free(*cmds);
	return (1);
}

int	run_minishell(t_compound	*cmds)
{
	HIST_ENTRY	**history_list;
	char		*str;
	int			i;

	cmds->exit_status = 0;
	while(TRUE)
	{
		str = readline("\033[32mf\033[35mz\033[32msh\033[0m \xF0\x9F\x90\xB3 ");
		// str = readline("fzsh: ");
		if (!all_space(str))
		{
			if (str[0] != ' ')
				add_history(str);
			run_procces(cmds, str);
		}
	}
	return (0);
}

