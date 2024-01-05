#include "../minishell.h"

void	sighandler(int signum)
{
	// printf("Signal: %d\n", signum);
	exit(1);
}

int main()
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
	
	str = readline("minishell: ");
	while (str != NULL)					// use cntl+d to get the NULL
	{
		add_history(str);
		free (str);
		str = readline("minishell: ");
	}
	his_list = history_list();
	while (his_list != NULL && his_list[i] != NULL)
	{
		printf("\ndata %d: %p\n", i + 1, his_list[i]->data);				// idk how to use: it always comes as null
		// free(his_list[i]->data);
		printf("line %d: %s\n", i + 1, his_list[i]->line);
		free(his_list[i]->line);
		printf("time %d: %s\n", i + 1, his_list[i]->timestamp);		// idk how to use: it always comes as \0
		// free(his_list[i]->timestamp);
		free(his_list[i]);
		i++;
	}
	free(his_list);
	// rl_clear_history();	
}

// not clear what does rl_clear_history free (if anything) 
