/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_transfer_ll_to_ptr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:27:07 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	pro_ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*pro_ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*ptr;

	s1_len = pro_ft_strlen(s1);
	s2_len = pro_ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i] != '\0' && i < s1_len && s1_len != 0)
	{
		ptr[i] = s1[i];
		i++;
	}
	if (s1_len != 0)
	{
		ptr[i] = '=';
		ptr[i + 1] = '\0';
	}
	if (s2 != NULL)
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

void	print_double_ptr(t_compound *cmds)
{
	int	i;

	i = 0;
	while (cmds->envp[i])
	{
		write (1, cmds->envp[i], pro_ft_strlen(cmds->envp[i]));
		write (1, "\n", 1);
		i++;
	}
}

int	ft_transfer_ll_to_env_ptr(t_compound *cmds)
{
	int		i;
	int		length;
	t_env	*temp;

	i = -1;
	length = 0;
	temp = cmds->env_ll;
	if (cmds->envp)
		free_double_ptr(cmds->envp);
	cmds->envp = (char **)malloc(sizeof(char *) * (ft_count_nodes(cmds) + 1));
	if (!cmds->envp)
		return (0);
	cmds->envp[ft_count_nodes(cmds)] = NULL;
	while (temp != NULL)
	{
		if (temp->env_display == TRUE)
		{
			length = pro_ft_strlen(temp->key) + pro_ft_strlen(temp->value);
			cmds->envp[++i] = pro_ft_strjoin(temp->key, temp->value);
			if (!cmds->envp[i])
				return (free_double_ptr(cmds->envp), FALSE);
		}
		temp = temp->next;
	}
	return (TRUE);
}
