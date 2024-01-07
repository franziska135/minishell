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
	// t_compound	cmds = struct_init();

	// print_struct(cmds);

printf("1:"); syntax("echo \"Hello\" | | wc -l");
printf("2:"); syntax("ls | sort -r >");
printf("3:"); syntax("cat file.txt | grep \"pattern\" >>");
printf("4:"); syntax("command1 || | command2");
printf("5:"); syntax("echo \"Error\" 2>& | grep \"Error\"");
printf("6:"); syntax("ls | wc -l > output.txt | cat");
printf("7:"); syntax("echo \"Hello\" > output.txt < input.txt");
printf("8:"); syntax("ls | sort -r > | cat");
printf("9:"); syntax("cat file.txt | grep \"pattern\" 2>/dev/null || command2");
printf("10:"); syntax("command1 || && command2");
printf("11:"); syntax("echo \"Hello\" | wc -l > output.txt | cat");
printf("12:"); syntax("ls > file.txt | wc -l");
printf("13:"); syntax("cat file.txt | grep \"pattern\" >> output.txt ||");
printf("14:"); syntax("echo \"Error\" 2>&1 | grep \"Error\" || command2");
printf("15:"); syntax("ls | sort -r | cat >");
printf("16:"); syntax("echo \"Hello\" | > output.txt");
printf("17:"); syntax("ls | sort -r > file.txt | cat");
printf("18:"); syntax("cat file.txt | grep \"pattern\" > output.txt || | command2");
printf("19:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\"");
printf("20:"); syntax("ls | sort -r > file.txt > output.txt");
printf("21:"); syntax("echo \"Hello\" | wc -l > output.txt < input.txt | cat");
printf("22:"); syntax("ls | sort -r > file.txt > | cat");
printf("23:"); syntax("cat file.txt | grep \"pattern\" > output.txt 2>&1 || command2");
printf("24:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\" || command2");
printf("25:"); syntax("ls | sort -r > file.txt | cat >");
printf("26:"); syntax("echo \"Hello\" | wc -l > output.txt || | cat");
printf("27:"); syntax("ls | sort -r > file.txt > output.txt | cat");
printf("28:"); syntax("cat file.txt | grep \"pattern\" > output.txt | command2");
printf("29:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\" ||");
printf("30:"); syntax("ls | sort -r > file.txt > output.txt | cat >");
printf("31:"); syntax("echo \"Hello\" > output.txt < input.txt | cat > file.txt");
printf("32:"); syntax("ls > file.txt | wc -l | sort -r");
printf("33:"); syntax("cat file.txt | grep \"pattern\" > output.txt | command2 | wc -l");
printf("34:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\" || | command2");
printf("35:"); syntax("ls | sort -r > file.txt > output.txt | cat | wc -l");
printf("36:"); syntax("echo \"Hello\" | wc -l > output.txt | cat > file.txt | sort -r");
printf("37:"); syntax("ls > file.txt | wc -l | sort -r >");
printf("38:"); syntax("cat file.txt | grep \"pattern\" > output.txt | command2 | wc -l |");
printf("39:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\" || | command2 | wc -l");
printf("40:"); syntax("ls | sort -r > file.txt > output.txt | cat | wc -l");
printf("41:"); syntax("echo \"Hello\" | wc -l > output.txt | cat > file.txt | sort -r");
printf("42:"); syntax("ls > file.txt | wc -l | sort -r >");
printf("43:"); syntax("cat file.txt | grep \"pattern\" > output.txt | command2 | wc -l |");
printf("44:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\" || | command2 | wc -l");
printf("45:"); syntax("ls | sort -r > file.txt > output.txt | cat | wc -l");
printf("46:"); syntax("echo \"Hello\" | wc -l > output.txt | cat > file.txt | sort -r");
printf("47:"); syntax("ls > file.txt | wc -l | sort -r >");
printf("48:"); syntax("cat file.txt | grep \"pattern\" > output.txt | command2 | wc -l |");
printf("49:"); syntax("command1 || echo \"Error\" 2>&1 | grep \"Error\" || | command2 | wc -l");
printf("50:"); syntax("ls | sort -r > file.txt > output.txt | cat | wc -l");

	// struct_free(cmds);

}