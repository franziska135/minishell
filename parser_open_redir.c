#include "minishell.h"

static char	**redir_expand(t_compound *cmds, char *token)
{
	char	*new_token;
	char	*ret;
	char	**split_token;


	new_token = expand_redir(cmds, token);
	if (!new_token)
		return (NULL);
	split_token = expansion_split(new_token);
	free(new_token);
	if (!split_token)
		return (NULL);
	if (!split_token[0] || split_token[1])
	{
		dpointer_free(split_token);
		return (NULL);
	}
	split_token[0] = remove_quotes(split_token[0]);
	return (split_token);
}


static void	redir_out(t_compound *cmds, char *file, int pipe, size_t *i)
{
	char	**str;

	*i += 1;
	if (cmds->scmd[pipe].out_fd == -1 || cmds->scmd[pipe].in_fd == -1)
		cmds->scmd[pipe].out_fd = -1;
	if (cmds->scmd[pipe].out_fd)
		close (cmds->scmd[pipe].out_fd);
	str = redir_expand(cmds, file);
	if (!str)
	{
		print_error(NULL, file, "ambiguous redirect");
		cmds->scmd[pipe].out_fd = -1;
	}
	else
	{
		cmds->scmd[pipe].out_fd = open(*str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmds->scmd[pipe].out_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}

static void	redir_in(t_compound *cmds, char *file, int pipe, size_t *i)
{
	char	**str;

	*i += 1;
	if (cmds->scmd[pipe].out_fd == -1 || cmds->scmd[pipe].in_fd == -1)
		cmds->scmd[pipe].in_fd = -1;
	if (cmds->scmd[pipe].in_fd)
		close (cmds->scmd[pipe].in_fd);
	str = redir_expand(cmds, file);
	if (!str)
	{
		print_error(NULL, file, "ambiguous redirect");
		cmds->scmd[pipe].in_fd = -1;
	}
	else
	{
		cmds->scmd[pipe].in_fd = open(*str, O_RDONLY);
		if (cmds->scmd[pipe].in_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
}


static void	redir_append(t_compound *cmds, char *file, int pipe, size_t *i)
{
	char	**str;

	*i += 1;
	if (cmds->scmd[pipe].out_fd == -1 || cmds->scmd[pipe].in_fd == -1)
		cmds->scmd[pipe].out_fd = -1;
	if (cmds->scmd[pipe].out_fd)
		close (cmds->scmd[pipe].out_fd);
	str = redir_expand(cmds, file);
	if (!str)
	{
		print_error(NULL, file, "ambiguous redirect");
		cmds->scmd[pipe].out_fd = -1;
	}
	else
	{
		cmds->scmd[pipe].out_fd = open(*str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmds->scmd[pipe].out_fd == -1)
			print_error(NULL, *str, strerror(errno));
		dpointer_free(str);
	}
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
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "|", 2))
			pipe++;
		else if (!ft_strncmp(tokens[i], ">", 2) && cmds->scmd[pipe].out_fd != -1)
			redir_out(cmds, tokens[i + 1], pipe, &i);
		else if (!ft_strncmp(tokens[i], "<", 2) && cmds->scmd[pipe].in_fd != -1)
			redir_in(cmds, tokens[i + 1], pipe, &i);
		else if (!ft_strncmp(tokens[i], ">>", 3) && cmds->scmd[pipe].out_fd != -1)
			redir_append(cmds, tokens[i + 1], pipe, &i);
		i++;
	}
	return (tokens);
}
