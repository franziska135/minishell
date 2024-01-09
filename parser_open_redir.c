#include "minishell.h"

static int	redir_out(char *str, int fd)
{
	int	new_fd;
	if (fd == -1)
		return (-1);
	if (fd)
		close (fd);
	// 			EXPAND
	str = remove_quotes(str);
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	return (fd);
}

static int	redir_in(char *str, int fd)
{
	if (fd == -1)
		return (-1);
	if (fd)
		close (fd);
	// 			EXPAND
	str = remove_quotes(str);
	fd = open(str, O_RDONLY);
	return (fd);
}


static int	redir_append(char *str, int fd)
{
	if (fd == -1)
		return (-1);
	if (fd)
		close (fd);
	// 			EXPAND
	str = remove_quotes(str);
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0664);
	return (fd);
}

static void	redir_hd(t_compound *cmds, char **tokens)
{
	char	*str;
	int		fd;
	size_t	i;
	int		pipe;

	if (fd)
		close (fd);
	i = 0;
	pipe = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		if (!ft_strncmp(tokens[i], "<<", 3))
		{
			str = remove_quotes(tokens[i + 1]);
			cmds->scmd[pipe].in_fd = ft_here_doc(str);
		}
		i++;
	}
}

int	open_redir(t_compound *cmds, char **tokens)
{
	size_t	i;
	int		pipe;

	i = 0;
	pipe = 0;
	redir_hd(cmds, tokens);
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		else if (!ft_strncmp(tokens[i], ">", 2))
			cmds->scmd[pipe].out_fd = redir_out(tokens[i + 1], cmds->scmd[pipe].out_fd);
		else if (!ft_strncmp(tokens[i], "<", 2))
			cmds->scmd[pipe].in_fd = redir_in(tokens[i + 1], cmds->scmd[pipe].in_fd);
		else if (!ft_strncmp(tokens[i], ">>", 3))
			cmds->scmd[pipe].out_fd = redir_append(tokens[i + 1], cmds->scmd[pipe].out_fd);
		i++;
	}
	return (1);
}
