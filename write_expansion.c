#include "minishell.h"

static int	write_expansion(t_compound *cmds, char *token, int fd, int fd_flag, int flag)
{
	t_env	*env;
	char	*key;
	size_t	i;
	int		ret;

	token++;
	ret = 0;
	key = find_key(token);
	if (key)
	{
		env = find_node(cmds, key);
		ret = ft_strlen(key);
		free(key);
		if (env && env->value)
		{
			write(fd, env->value, ft_strlen(env->value));
			i = 0;
			while (i < ft_strlen(env->value))
			{
				ft_putnbr_fd(flag, fd_flag);
				i++;
			}
			return (ret);
		}
	}
	else if (token[0] == '?')
	{
		if (WIFEXITED(cmds->exit_status))
			ft_putnbr_fd(WEXITSTATUS(cmds->exit_status), fd);
		else
			write (fd, "0", 1);
		// check for how many digits;
		ft_putnbr_fd(flag, fd_flag);
		ret++;
	}
	else if ((token[0] != '_' && token[0] != '"' && token[0] != '\'' && !ft_isalpha(token[0])) || flag != 0)
	{
		write(fd, "$", 1);
		ft_putnbr_fd(flag, fd_flag);
	}
	return (ret);
}