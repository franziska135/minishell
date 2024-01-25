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

//at some point: check if PWd/OLDPWD is updated correctly
//check the buffer size of pwd[]
//find_needle & update blah do NOTHING, if anything is NULL/not found
//but what happens with chdir and getcwd?
//fix what happens if error statement is printed

void	builtin_cd(t_simple *scmd, t_compound *cmds)
{
	if (!scmd->cmd[1])
		builtin_cd_home(cmds);
	else if (scmd->cmd[2])
		print_error("bash: ", "cd: ", NULL, "too many arguments");
    else if (ft_strncmp(scmd->cmd[1], "..", 2) == 0)
		builtin_cd_dotdot(cmds);
	else if (ft_strncmp(scmd->cmd[1], "-", 1) == 0)
        builtin_cd_back(cmds);
	else
        builtin_cd_path(cmds, scmd);
	//can be removed later:
	builtin_pwd();
}

//what happens on errors? go back to history promt?
//what's the error if chdir fails?
void    builtin_cd_home(t_compound *cmds)
{
    t_env	*node;
    char    pwd[100];

    node = find_node(cmds, "HOME");
    if (node != NULL && node->value != NULL)
	{
        update_env_ll(cmds, "OLDPWD", getcwd(pwd, 100));
		chdir(node->value);
		update_env_ll(cmds, "PWD", getcwd(pwd, 100));
    }
	else
		print_error("bash: ", "cd: ", NULL, "HOME not set");
}

//what happens on errors? go back to history promt?
//what's the error if chdir fails?
void    builtin_cd_dotdot(t_compound *cmds)
{
    char    pwd[100];

    update_env_ll(cmds, "OLDPWD", getcwd(pwd, 100));
	chdir("..");
	update_env_ll(cmds, "PWD", getcwd(pwd, 100));
}

//what happens on errors? go back to history promt?
//what's the error if chdir fails?
void    builtin_cd_back(t_compound *cmds)
{
    char    pwd[100];
    t_env   *node;
    char    *tmp;

    node = find_node(cmds, "OLDPWD");
    if (node != NULL && node->value != NULL)
	{
        tmp = getcwd(pwd, 100);
        chdir(node->value);
        update_env_ll(cmds, "OLDPWD", tmp);
        update_env_ll(cmds, "PWD", getcwd(pwd, 100));
    }
	else
		print_error("bash: ", "cd: ", NULL, "OLDPWD not set");
}

//what's the error if chdir fails?
void    builtin_cd_path(t_compound *cmds, t_simple *scmd)
{
    t_env   *node;
    char    pwd[100];
    char    *tmp;

    tmp = getcwd(pwd, 100);
    if (chdir(scmd->cmd[1]) == 0)
    {
        update_env_ll(cmds, "OLDPWD", tmp);
    	update_env_ll(cmds, "PWD", getcwd(pwd, 100));
    }
	else //on chdir == -1
		print_error("bash: ", "cd: ", scmd->cmd[1], strerror(errno));
}