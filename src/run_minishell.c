/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:19 by mzolfagh         ###   ########.fr       */
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

	non_interactive_mode();
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

int	run_minishell(t_compound	*cmds)
{
	HIST_ENTRY	**history_list;
	char		*str;
	int			i;

	cmds->exit_status = 0;
	while (1)
	{
		interactive_mode();
		if (g_signal == 130)
		{
			cmds->exit_status = 130;
			g_signal = 0;
		}
		if (isatty(fileno(stdin)))
			str = readline("\x1b[32mf\x1b[35mz\x1b[32msh\x1b[34m \xf0\x9f\x90\x8b \x1b[0m ");
		else
		{
			char	*line;
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
			add_history(str);
			run_procces(cmds, str);
		}
	}
	return (1);
}
