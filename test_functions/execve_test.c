#include "../minishell.h"

int main(int ac, char *av[], char *envp[])
{
	pid_t pid;
	char *str[] = {"cat", "" , "" ,"-e", NULL};
	


	execve("/bin/cat", str, envp);
}
