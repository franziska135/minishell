/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 14:24:16 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// readline is apparently not part of standard library to use it in my pc i
//needed to install the readline library
// to compile:	cc readline.c -lreadline
void	sighandler(int signum)
{
	// printf("Signal: %d\n", signum);
	exit(1);
}

int	main(void)
{
	char					*str;
    struct sigaction		sa;
	HIST_ENTRY				**history_list;

	//waits for ctrl+c
	sa.sa_handler = sighandler;
	if (sigaction(SIGINT, &sa, NULL) == -1) 
		perror(NULL);
	else if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror(NULL);
	// like getnextline malloc, unlike gnl doesnt include \n
	str = readline("minishell: ");
	if (!str)
		return (0);
	printf("what you typed: %s\n", str);
	add_history(str);
	free (str);
	rl_redisplay();
	// printf("from history: %s\n", str);
	rl_clear_history();
}
// when readline is running if i press cntrl+d we have segfault. 
//The way around it is to define your own binding for signals
// as the subject says, readline has huge memory leaks!!