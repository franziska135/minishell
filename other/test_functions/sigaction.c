#include "../minishell.h"

void	sighandler(int signum)
{
	// printf("Signal: %d\n", signum);
	exit(1);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = sighandler;
	
	if (sigaction(SIGINT, &sa, NULL) == -1)			//waits for ctrl+c 
		perror(NULL);
	else if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror(NULL);

	pid_t	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			printf("waiting for termination...\n");
			usleep(300000);
		}
	}

	sleep(5);											//waits 5 sec and kill the child
	kill(pid, SIGKILL);
	sleep(2);

	wait(NULL);
} 