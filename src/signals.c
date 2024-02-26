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
	if (g_signal != 0)
		set_status(cmds, g_signal);
	g_signal = 0;
	signal(SIGQUIT, &backslash_non_interactive);
	signal(SIGINT, &ctrlc_non_interactive);
}

void	interactive_mode(t_compound *cmds)
{
	if (g_signal != 0)
		set_status(cmds, g_signal);
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_handler);
}

void	signal_hd(t_compound *cmds)
{
	if (g_signal != 0)
		set_status(cmds, g_signal);
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_hd);
}
