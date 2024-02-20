#include "minishell.h"

static void	expand_env(t_env *env, int fd[2][2], int flag)
{
	size_t	i;

	write(fd[0][1], env->value, ft_strlen(env->value));
	i = 0;
	while (i < ft_strlen(env->value))
	{
		ft_putnbr_fd(flag, fd[1][1]);
		i++;
	}
}

static int	expand_exit_status(t_compound *cmds, int fd, int fd_flag, int flag)
{
	int	ret;
	int	nbr;
	int	i;

	i = 0;
	ret = 0;
	nbr = WEXITSTATUS(cmds->exit_status);
	if (WIFEXITED(cmds->exit_status))
	{
		ft_putnbr_fd(WEXITSTATUS(cmds->exit_status), fd);
		if (nbr == 0)
			(ft_putnbr_fd(flag, fd_flag), ret++);
		while (nbr)
		{
			(ft_putnbr_fd(flag, fd_flag), ret++);
			nbr /= 10;
		}
	}
	else
	{
		write (fd, "0", 1);
		ft_putnbr_fd(flag, fd_flag);
		ret++;
	}
	return (ret);
}

int	write_expansion(t_compound *cmds, char *token, int fd[2][2], int flag)
{
	t_env	*env;
	char	*key;
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
			return (expand_env(env, fd, flag), ret);
	}
	else if (token[0] == '?')
		ret += expand_exit_status(cmds, fd[0][1], fd[1][1], flag);
	else if ((token[0] != '_' && token[0] != '"' && token[0] != '\''
			&& !ft_isalpha(token[0])) || flag != 0)
	{
		write(fd[0][1], "$", 1);
		ft_putnbr_fd(flag, fd[1][1]);
	}
	return (ret);
}
