#include "../minishell.h"

int main()
{
	char	*str;

	str = readline("minishell: ");
	if (!str)
		return (0);
	printf("input: %s\n", str);
	free(str);
	rl_on_new_line();							// tells the readline lib that cursor is on the new line
	rl_replace_line("Thank you for using minishell.\n", 0);		// second input is clear undo and is set to 0 to not clear the undo (what is clear undo you ask, idk)
 	rl_point = rl_end;							// so if we dont have this line, rl_replace just desplays the first n char of the string its given. n is how many chars the input had in readline.
	rl_redisplay();
 	rl_clear_history();
}