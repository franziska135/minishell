#include "minishell.h"

t_compound struct_init()
{
	t_compound	compound;
	t_simple	*s_cmd;

	s_cmd = malloc(sizeof(t_simple) * 2);
	s_cmd[0].cmd = ft_split("Hello World!", ' ');
	s_cmd[0].in_fd = 0;
	s_cmd[0].out_fd = 1;

	s_cmd[1].cmd = ft_split("goodbye HELL", ' ');
	s_cmd[1].in_fd = 3;
	s_cmd[1].out_fd = 4;
	
	compound.nbr_scmd = 2;
	compound.scmd = s_cmd;




	return(compound);
}

int main()
{
	// t_compound	cmds = struct_init();

	// print_struct(cmds);
	parser("as>|' |\"|' |as\"| ");
	// struct_free(cmds);

}