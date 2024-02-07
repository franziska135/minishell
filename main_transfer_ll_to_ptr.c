/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 15:24:47 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function returns 1 if a builtin matched
//0 if no builtin matched
//open issues:
//valgrind for cd, pwd, env, echo, unset okay
//restructure export
//if PATH is currently unset, value of PATH is empty
//and function returns nothing 
/***************THIS IS TO TRANSFER LL TO DOUBLE PTR**************/
	/*(the function is in this file, scoll up:)*/
	// int i = 0;
	// ft_transfer_ll_to_ptr(cmds);
	// while (cmds->envp[i])
	// {
	// 	write (1, cmds->envp[i], ft_strlen(cmds->envp[i]));
	// 	write (1, "\n", 1);
	// 	i++;
	// }
	/******************************************************************/
	//if a buitin matched, the return will be 1
char	*pro_ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	int		i;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!ptr)
		return (0);
	// i = s1_len + 1 --> strjoin
	i = 0;
	while (s1[i] != '\0' && i < s1_len - 1 && s1_len != 0)
	{
		ptr[i] = s1[i];
		i++;
	}
	if (s1_len != 0)
	{
		ptr[i] = '=';
		ptr[i + 1] = '\0';
	}
	ft_strlcat(ptr, s2, s1_len + 1 + s2_len + 1);
	return (ptr);
}

int	ft_count_nodes(t_compound *cmds)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = cmds->env_ll;
	while (temp != NULL)
	{
		if (temp->env_display == TRUE)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	ft_transfer_ll_to_ptr(t_compound *cmds)
{
	int		i;
	int		length;
	t_env	*temp;

	i = 0;
	length = 0;
	temp = cmds->env_ll;
	if (cmds->envp)
		free_double_ptr(cmds->envp);
	cmds->envp= (char **)malloc(sizeof(char *) * (ft_count_nodes(cmds) + 1));
	if (!cmds->envp)
		return (0);
	cmds->envp[ft_count_nodes(cmds)] = NULL;
	while (temp != NULL)
	{
		if (temp->env_display == TRUE)
		{
			length = ft_strlen(temp->key) + ft_strlen(temp->value);
			cmds->envp[i] = (char *)malloc((length + 1) * sizeof(char));
			if (!cmds->envp[i])
				return (free_double_ptr(cmds->envp), FALSE);
			if (temp->value)
				cmds->envp[i] = pro_ft_strjoin(temp->key, temp->value);
			else
				cmds->envp[i] = ft_strjoin(temp->key, "=");
			i++;
		}
		temp = temp->next;
	}
	i = 0;
	while (cmds->envp[i])
	{
		write (1, cmds->envp[i], ft_strlen(cmds->envp[i]));
		write (1, "\n", 1);
		i++;
	}
	return (TRUE);
}