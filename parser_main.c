#include "minishell.h"

t_compound	parser(char *str);


t_compound struct_init()
{
	t_compound	compound;
	t_simple	*s_cmd;

	s_cmd = malloc(sizeof(t_simple) * 2);
	s_cmd[0].command = ft_split("Hello World!", ' ');
	s_cmd[0].hd_delimiter = ft_split("DEL LIMIT ER", ' ');
	s_cmd[0].in_fd = 0;
	s_cmd[0].out_fd = 1;

	s_cmd[1].command = ft_split("goodbye HELL", ' ');
	s_cmd[1].hd_delimiter = ft_split("ER LIMIT DEL", ' ');
	s_cmd[1].in_fd = 3;
	s_cmd[1].out_fd = 4;
	
	compound.amt_simple_cmds = 2;
	compound.cmd = s_cmd;

	return(compound);
}

void	print_dpointer(char **str)
{
	int	i = 0;

	while (str[i])
	{
		printf("%s, ", str[i]);
		i++;
	}
	printf ("\n");
}

void	print_struct(t_compound compound)
{
	int		i = 0;

	while (i < compound.amt_simple_cmds)
	{
		printf("\nPipe %d:\n", i + 1);
		printf("commands: ");
		print_dpointer(compound.cmd[i].command);

		printf("delimiters: ");
		print_dpointer(compound.cmd[i].hd_delimiter);

		printf ("in_fd: %d\t\tout_fd:%d\n", compound.cmd[i].in_fd, compound.cmd[i].out_fd);
		i++;
	}
}

int main()
{
	t_compound	compound = struct_init();
	compound = struct_init();
	
	char		*str = readline("fzsh: ");

	// compound = parser(str);


	print_struct(compound);

}