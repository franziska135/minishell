#include "minishell.h"

char	**scmds_expand(t_compound *cmds, char **scmds)
{
	int		fd[2];
	int		i;
	char	*gnl;
	char	**split;

	if (pipe(fd) == -1)
		return (NULL);
	i = 0;
	while (scmds[i])
	{
		expand_token(cmds, scmds[i], fd);
		write(fd[1], " ", 1);
		i++;
	}
	write(fd[1], "\0", 1);
	close(fd[1]);
	gnl = get_next_line(fd[0]);
	close(fd[0]);
	if (!gnl || gnl[0] == '\0')
		return (dpointer_free(scmds), free(gnl), NULL);
	split = expansion_split(gnl);
	free(gnl);
	dpointer_free(scmds);
	return (split);
}
