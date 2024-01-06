#include "minishell.h"

t_compound	parser(char *str);

void	dpointer_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	struct_free(t_compound cmds)
{
	int		i;

	i = 0;
	while (i < cmds.nbr_scmd)
	{
		dpointer_free(cmds.scmd[i].cmd);
		i++;
	}
	free(cmds.scmd);
}
void	err_handler(char *str)
{
	printf("%s\n", str);
}

