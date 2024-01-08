#include "minishell.h"

// t_compound struct_init()
// {
// 	t_compound	cmds;
// 	t_simple	*scmd;

// 	scmd = malloc(sizeof(t_simple) * 2);
// 	scmd[0].cmd = ft_split("Hello World!", ' ');
// 	scmd[0].in_fd = 0;
// 	scmd[0].out_fd = 1;

// 	scmd[1].cmd = ft_split("goodbye HELL", ' ');
// 	scmd[1].in_fd = 3;
// 	scmd[1].out_fd = 4;
	
// 	cmds.nbr_scmd = 2;
// 	cmds.scmd = scmd;




// 	return(cmds);
// }

int main()
{
	char	*str;
	char	**tokens;
	char	*str1 = "echo 123 >| cat >> infile | <<out   ";

	str = malloc(sizeof(char) * 100);
	ft_strlcpy(str, str1, ft_strlen(str1));
	
	if (!syntax(str))
		return (free(str), 1);
	tokens = lexis(str);
	if (!tokens)
		return (free(str), 1);
	
	
	int i = 0;
	while (tokens[i])
	{
		printf("%s$\n", tokens[i]);
		i++;
	}
	printf("%s$\n", tokens[i]);

	dpointer_free(tokens);
	free(str);

}