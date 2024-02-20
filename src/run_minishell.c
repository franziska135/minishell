/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2023/11/27 16:12:30 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	all_space(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}


static int	run_procces(t_compound	*cmds, char *str)
{
	char	**tokens;

	
	if (!syntax(str, cmds))
		return (free(str), 0);
	tokens = lexis(str);
	if (!tokens)
		return (0);
	tokens = parser(cmds, tokens);
	if (!tokens)
		return (0);
	dpointer_free(tokens);
	if (!piping_root(cmds))
		return (0);
	struct_free(*cmds);
	return (1);
}

void	ctrlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		// printf("%d\n", g_signal);
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	//ioctl(0, TIOCSTI, "\n");
}

// void	quit_handler(int sig)
// {
// 	if 
// }

int	run_minishell(t_compound	*cmds)
{
	HIST_ENTRY	**history_list;
	char		*str;
	int			i;

	signal(SIGQUIT, SIG_IGN);
	cmds->exit_status = 0;
	while (1)
	{
		signal(SIGINT, &ctrlc_handler);
		if (g_signal == 130)
		{
			cmds->exit_status = 130;
			g_signal = 0;
		}
		//str = readline("\x1b[32mf\x1b[35mz\x1b[32msh\x1b[34m \xf0\x9f\x90\x8b \x1b[0m ");
		if (isatty(fileno(stdin)))
			str = readline("\x1b[32mf\x1b[35mz\x1b[32msh\x1b[34m \xf0\x9f\x90\x8b \x1b[0m ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			str = ft_strtrim(line, "\n");
			free(line);
		}
		if (str == NULL)
		{
			cmds->exit_status = 0;
			break ;
		}
		if (!all_space(str))
		{
			if (str[0] != ' ')
				add_history(str);
			run_procces(cmds, str);
		}
	}
	return (1);
}
