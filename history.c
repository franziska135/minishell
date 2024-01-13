#include "minishell.h"

static int	run_procces(char *str)
{
	t_compound	cmds;
	char		**tokens;
	
	if (!syntax(str))
		return (free(str), 0);
	tokens = lexis(str);
	if (!tokens)
		return (free(str), 0);

	// int i = 0;
	// while (tokens[i])
	// {
	// 	printf("%s$\n", tokens[i]);
	// 	i++;
	// }
	// printf("%s$\n\n", tokens[i]);

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

	while(TRUE)
	{
		str = readline("fzsh: ");
		if (!str)
			return (0);
		if (str[0])
		{
			if (!str[0] == ' ')
				add_history(str);
			run_procces(str);
		}

	}
		
}

