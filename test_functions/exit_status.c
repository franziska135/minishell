#include "../minishell.h"

int main()
{
	int status = 2 << 8;
	printf("%d\n", WEXITSTATUS(status));
	printf("%d\n", WIFEXITED(status));

}