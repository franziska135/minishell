#include "minishell.h"

static size_t	pipe_count(char **tokens)
{
	size_t	i;
	size_t	nbr_pipe;


	i = 0;
	nbr_pipe = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			nbr_pipe++;
		i++;
	}
	return (nbr_pipe);
}



t_compound	parser(char **tokens)
{
	t_compound	cmds;

	cmds.nbr_scmd = pipe_count(tokens) + 1;
	cmds.scmd = (t_simple *)malloc(sizeof(t_simple) * cmds.nbr_scmd);
	struct_nullifier(&cmds);
	cmds.nbr_scmd = pipe_count(tokens) + 1;
	open_redir(&cmds, tokens);
	
	return(cmds);
}