/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:26:24 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_interactive_mode(t_compound *cmds)
{
	if (g_signal == 2)
		set_status(cmds, 130);
	else if (g_signal == 3)
		set_status(cmds, 131);
	g_signal = 0;
	signal(SIGQUIT, &backslash_non_interactive);
	signal(SIGINT, &ctrlc_non_interactive);
}

void	interactive_mode(t_compound *cmds)
{
	if (g_signal == 2)
		set_status(cmds, 130);
	else if (g_signal == 3)
		set_status(cmds, 131);
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_handler);
}

void	signal_hd(t_compound *cmds)
{
	if (g_signal == 2)
		set_status(cmds, 130);
	else if (g_signal == 3)
		set_status(cmds, 131);
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_hd);
}

void	deactivate_c(int sig)
{
	if (sig == SIGINT)
	write (2, "cntrlc", 7);
}

void	deactivate_slash(int sig)
{
	if (sig == SIGQUIT)
		write (1, "slash", 6);
}

void	signal_inhibition(t_compound *cmds)
{
	if (ft_strncmp(cmds->scmd->cmd[0], "./minishell", 12) == 0)
	{
		if (g_signal == 2)
			set_status(cmds, 130);
		else if (g_signal == 3)
			set_status(cmds, 131);
		g_signal = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
