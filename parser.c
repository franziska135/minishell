#include "minishell.h"

size_t	pipe_count(char **tokens)
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
	if (!open_redir(&cmds, tokens))
		err_handler("OPENFILE ERROR");
	return(cmds);
}