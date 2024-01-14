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


static int	run_procces(char *str)
{
	t_compound	cmds;
	char		**tokens;
	
	if (!syntax(str))
		return (free(str), 0);
	tokens = lexis(str);
	if (!tokens)
		return (free(str), 0);
	cmds = parser(tokens);
	if (!struct_cpy(&cmds, tokens))
		return (0);
	print_struct(cmds);
	dpointer_free(tokens);
	struct_free(cmds);
}

int	history()
{
	HIST_ENTRY	**history_list;
	char		*str;
	int			i;
	rl_initialize();
	using_history();
	while(TRUE)
	{
		str = readline("fzsh: ");
		if (!all_space(str))
		{
			if (str[0] != ' ')
				add_history(str);
			run_procces(str);
		}
		// rl_replace_line("", 0);
        // rl_redisplay();
	}
	return (0);
}

