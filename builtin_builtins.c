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
	if (!s_cmd->cmd[1])
	{
		if (getenv("HOME") != NULL)
			chdir(getenv("HOME"));//what's the error if chanign directories didn't work?
		else
			print_error("bash: ", "cd: ", NULL, "HOME not set");
	}
	else if (s_cmd->cmd[2])
		print_error("bash: ", "cd: ", NULL, "too many arguments");
	else if (ft_strncmp(s_cmd->cmd[1], "..", 2) == 0)
		chdir("..");
		//print_error("bash: ", "cd: ", s_cmd->cmd[1], strerror(errno));
		//-1 on failure, what's the error if chanign directories didn't work?
	else if (ft_strncmp(s_cmd->cmd[1], "-", 1) == 0)
	{
		if (getenv("OLDPWD") != NULL)
			chdir("OLDPWD");//-1 on failure, what's the error if chanign directories didn't work?
		else
			print_error("bash: ", "cd: ", NULL, "OLDPWD not set");
	}
	else
	{
		if (chdir(s_cmd->cmd[1]) == -1)
			print_error("bash: ", "cd: ", s_cmd->cmd[1], strerror(errno));
	}
	//can be removed later:
	builtin_pwd();
}

void	builtin_envp(t_compound *compound)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	write (2, "-------ENV START-------------\n", 30);
	while (compound->envp[i])
	{
		write(1, compound->envp[i], ft_strlen(compound->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	write (2, "-------ENV END-------------\n", 28);
	//newline at the end?
}

void	builtin_echo(t_simple *s_cmd)
{
	int	i;
	int	start;

	i = 0;
	if (s_cmd->cmd[1])
	{
		//returns the index to the last occurence of -n...
		i = check_for_n(s_cmd);
		if (check_for_only_n(s_cmd->cmd[i]) == TRUE)
			builtin_echo_write(s_cmd, i);
		else
		{
			builtin_echo_write(s_cmd, 0);
			write (1, "\n", 1);
		}
	}
	else
		write (1, "\n", 1);
}

void	builtin_echo_write(t_simple *s_cmd, int i)
{
	int	start;

	start = i;
	if (s_cmd->cmd[i + 1])
		write (1, s_cmd->cmd[i + 1], ft_strlen(s_cmd->cmd[i + 1]));
	while (s_cmd->cmd[++i + 1])
	{
		write (1, " ", 1);
		write (1, s_cmd->cmd[i + 1], ft_strlen(s_cmd->cmd[i + 1]));
	}
}

int	check_for_n(t_simple *s_cmd)
{
	int		i;
	int		index_last_only_n;

	i = 1;
	index_last_only_n = 1;
	while (s_cmd->cmd[i] && check_for_only_n(s_cmd->cmd[i]) == TRUE)
	{
		index_last_only_n = i;
		i++;
	}
	return (index_last_only_n);
}

int		check_for_only_n(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
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
void	builtin_export(t_compound *compound)
{

}