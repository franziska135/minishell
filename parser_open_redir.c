#include "minishell.h"

static int	redir_out(char **str, int fd_out, int fd_in, size_t *i)
{
	*i += 1;
	if (fd_out == -1 || fd_in == -1)
		return (-1);
	if (fd_out)
		close (fd_out);
	fd_out = open(*str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_out == -1)
		perror("fzsh: ");
	return (fd_out);
}

static int	redir_in(char **str, int fd_in, int fd_out, size_t *i)
{
	*i += 1;
	if (fd_in == -1 || fd_out == -1)
		return (-1);
	if (fd_in)
		close (fd_in);
	fd_in = open(*str, O_RDONLY);
	if (fd_in == -1)
		perror("fzsh: ");
	return (fd_in);
}


static int	redir_append(char **str, int fd_out, int fd_in, size_t *i)
{
	*i += 1;
	if (fd_out == -1 || fd_in == -1)
		return (-1);
	if (fd_out)
		close (fd_out);
	fd_out = open(*str, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd_out == -1)
		perror("fzsh: ");
	return (fd_out);
}

static void	redir_hd(t_compound *cmds, char **tokens)
{
	size_t	i;
	int		pipe;

	i = 0;
	pipe = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		if (!ft_strncmp(tokens[i], "<<", 3))
		{
			if (cmds->scmd[pipe].in_fd)
				close (cmds->scmd[pipe].in_fd);
			i++;
			tokens[i] = remove_quotes(tokens[i]);
			cmds->scmd[pipe].in_fd = ft_here_doc(tokens[i]);
		}
		i++;
	}
}

char	**open_redir(t_compound *cmds, char **tokens)
{
	size_t	i;
	int		pipe;

	i = 0;
	pipe = 0;
	redir_hd(cmds, tokens);
	tokens = token_expand(cmds, tokens);
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		else if (!ft_strncmp(tokens[i], ">", 2))
			cmds->scmd[pipe].out_fd = redir_out(&tokens[i + 1], cmds->scmd[pipe].out_fd, cmds->scmd[pipe].in_fd, &i);
		else if (!ft_strncmp(tokens[i], "<", 2))
			cmds->scmd[pipe].in_fd = redir_in(&tokens[i + 1], cmds->scmd[pipe].in_fd, cmds->scmd[pipe].out_fd, &i);
		else if (!ft_strncmp(tokens[i], ">>", 3))
			cmds->scmd[pipe].out_fd = redir_append(&tokens[i + 1], cmds->scmd[pipe].out_fd, cmds->scmd[pipe].in_fd, &i);
		i++;
	}
	return (tokens);
}
