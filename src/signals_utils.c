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

void	ctrlc_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		ioctl(1, TIOCSTI, "\n");
		// write(STDERR_FILENO, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

//ctrl \ while a process is running
void	backslash_non_interactive(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal = 3;
		write (2, "Quit (core dumped)\n", 19);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

//ctrl -c while prompting
void	ctrlc_non_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

//ctrl -c while a process is running
void	ctrlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
