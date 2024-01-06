#include "minishell.h"

t_compound	parser(char *str)
{
	t_compound cmds;

	cmds = struct_init(str);
	printf("%zu\n", cmds.nbr_scmd);
}