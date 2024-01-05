/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2023/12/15 17:10:23 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

//what happens on error?
void	builtin_pwd(void)
{
	char	buf[100];

	if (getcwd(buf, 100) != NULL)
		write(1, buf, ft_strlen(buf));
	// else
	// 	printf("check");
	// 	perror(NULL);
	//can be removed?
	write (1, "\n", 1);
}

//how many digits shall be compared?
//-1 on failure, what's ther
void	builtin_cd(t_simple *s_cmd)
{
	char	*path_str;

	if (!s_cmd->command[1])
	{
		path_str = getenv("HOME");
		chdir(path_str);
		//-1 on failure, what's the error if chanign directories didn't work?
	}
	else if (ft_strncmp(s_cmd->command[1], "..", 2) == 0)
	{
		chdir("..");
		//print_error("bash: ", "cd: ", s_cmd->command[1], strerror(errno));
		//-1 on failure, what's the error if chanign directories didn't work?
	}
	else if (ft_strncmp(s_cmd->command[1], "-", 1) == 0)
	{
		path_str = getenv("OLDPWD");
		chdir(path_str);
		//-1 on failure, what's the error if chanign directories didn't work?
	}
	else
	{
		if (chdir(s_cmd->command[1]) == -1)
			print_error("bash: ", "cd: ", s_cmd->command[1], strerror(errno));
	}
	//can be removed later:
	builtin_pwd();
}

void	print_error(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		write (2, str1, ft_strlen(str1));
	if (str2)
		write (2, str2, ft_strlen(str2));
	if (str3)
	{
		write (2, str3, ft_strlen(str3));
		write (2, ": ", 2);
	}
	if (str4)
		write (2, str4, ft_strlen(str4));
	write (2, "\n", 1);
}

//unset needs a parameter to be passed with it-> error check
// void	ft_unset(t_list *m, char *str)
// {
// 	int	i;
// 	char *tmp;

// 	tmp = NULL;
// 	if (find_envp_path(m, str) == 1)
// 	{
// 		i = m->index_path;
// 		free(m->envp[m->index_path]);
// 		m->envp[m->index_path] = NULL;
// 		while (m->envp[i + 1])
// 		{
// 			tmp = ft_strdup(m->envp[i + 1]);
// 			if (!tmp)
// 				cleanup(m, EXIT);
// 			free(m->envp[i]);
// 			m->envp[i] = tmp; 
// 			i++;
// 		}
// 		if (tmp)
// 			(free(tmp), tmp = NULL);
// 		// if (m->envp[i])
// 		// 	free(m->envp[i]);
// 	}
// }

// // void	ft_echo(t_list *m)
// // {

// // }

// // void	ft_cd(t_list *m)
// // {

// // }

// // void	ft_export(t_list *m)
// // {
	
// // }
// void	ft_env(t_list *m)
// {
// 	int	i;

// 	i = 0;
// 	while (m->envp[i])
// 	{
// 		printf("%s\n", m->envp[i]);
// 		i++;
// 	}
// }
// // void	ft_exit(t_list *m)
// // {
	
// // }
