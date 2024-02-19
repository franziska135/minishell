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

void	handler(int sig)
{
	write (1, "stop allowed, cleaning started\n", 31);
	g_running = FALSE;
	write(1, "Signal handler called, g_running set to FALSE\n",  51);
	write(1, "EXIT_SUCCESS\n", 13);
	exit(EXIT_SUCCESS);
}

int	run_minishell(t_compound	*cmds)
{
	HIST_ENTRY	**history_list;
	struct		sigaction sa;
	char		*str;
	int			i;

	cmds->exit_status = 0;
	sa.sa_handler = &handler;
	sigaction(SIGINT, &sa, NULL);
	while (g_running == TRUE)
	{
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
			return (1);
		if (!all_space(str))
		{
			if (str[0] != ' ')
				add_history(str);
			run_procces(cmds, str);
		}
	}
	return (1);
}
