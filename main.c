#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	t_compound	cmds;

	init_env_llist(&cmds, envp);
	run_minishell(&cmds);
}
