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

void	sighandler(int signum)
{
	// printf("Signal: %d\n", signum);
	exit(1);
}

int	main(void)
{
	int					i = 0;
	char				*str;
    struct sigaction	sa;
	HIST_ENTRY			**his_list;

    sa.sa_handler = sighandler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror(NULL);
	// else if (sigaction(SIGQUIT, &sa, NULL) == -1)
	// 	perror(NULL);	
	// use cntl+d to get the NULL
	str = readline("minishell: ");
	while (str != NULL)
	{
		add_history(str);
		free (str);
		str = readline("minishell: ");
	}
	his_list = history_list();
	while (his_list != NULL && his_list[i] != NULL)
	{
		// idk how to use: it always comes as null
		printf("\ndata %d: %p\n", i + 1, his_list[i]->data);
		// free(his_list[i]->data);
		printf("line %d: %s\n", i + 1, his_list[i]->line);
		free(his_list[i]->line);
		// idk how to use: it always comes as \0
		printf("time %d: %s\n", i + 1, his_list[i]->timestamp);
		// free(his_list[i]->timestamp);
		free(his_list[i]);
		i++;
	}
	free(his_list);
	// rl_clear_history();	
}
// not clear what does rl_clear_history free (if anything) 
