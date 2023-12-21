#include "../minishell.h"

int main()
{
	sigset_t	signal_set;

	if (sigemptyset(&signal_set) == -1)			// initialises the struct
		perror(NULL);
	
	if (sigaddset(&signal_set, SIGINT) == -1)
		perror(NULL);

	// now SIGINT is added to signalset, i can not find any use-case for it 
	// without using fuctions like sigismember() or sigprocmask()

}