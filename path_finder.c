#include "./minishell.h"

static char	*path_access(char *path, char *cmd)
{
	char	**path_split;
	char	*tmp;
	int		j;

	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	j = 0;
	while (path_split[j])
	{
		tmp = ft_strjoin(path_split[j], "/");
		if (!tmp)
			return (dpointer_free(path_split), NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (dpointer_free(path_split), NULL);
		if (!access(path, F_OK | X_OK))
			return (dpointer_free(path_split), path);
		free(path);
		j++;
	}
	dpointer_free(path_split);
	print_error(NULL, cmd, "command not found.");
	return (NULL);
}

char	*path_finder(t_compound *cmds, int pipe)
{
	t_env	*env;

	if (!access(cmds->scmd[pipe].cmd[0], F_OK | X_OK))
		return (cmds->scmd[pipe].cmd[0]);
	env = find_node(cmds, "PATH");
	if (env && env->value)
		return (path_access(env->value, cmds->scmd[pipe].cmd[0]));
	return (NULL);
}