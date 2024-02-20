#include "../minishell.h"

// IT'S WRITTEN IN MANUAL TO NOT USE SIGNAL DUE TO PORTABILITY ISSUES
// SEE sigaction() INSTEAD

void	sighandler(int signum)
{
	printf("Signal: %d\n", signum);
	exit(1);
}

int main()
{
	pid_t	pid = fork();

	if (pid == 0)
	{
		if (signal(SIGINT, sighandler) == SIG_ERR)			//waits for ctrl+c
			perror(NULL);	
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