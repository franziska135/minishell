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

void	non_interactive_mode(void)
{
	g_signal = 0;
	signal(SIGQUIT, &backslash_non_interactive);
	signal(SIGINT, &ctrlc_non_interactive);
}

void	interactive_mode(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_handler);
}

void	signal_hd(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc_hd);

}

void	ctrlc_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = -1;
		write(1, "\n", 2);
		// rl_replace_line("", 1);
		// rl_on_new_line();
		// rl_redisplay();
		ioctl(0, TIOCSTI, "\n");
	}

}

//ctrl \ while prompting
void	backslash_non_interactive(int signum)
{
	if (signum == SIGQUIT)
	{
		write (2, "Quit (core dumped)\n", 19);
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
}

//ctrl -c while prompting
void	ctrlc_non_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
}
//ctrl -c while a process is running
void	ctrlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	//ioctl(0, TIOCSTI, "\n");
}
