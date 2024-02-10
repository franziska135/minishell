/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2023/11/27 16:12:30 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_word_count(char *str, char *flag)
{
	int	word_counter;
	int	word_begin;

	word_begin = 1;
	word_counter = 0;
	while (*str)
	{
		if (word_begin == 1 && *str != ' ')
		{
			word_counter++;
			word_begin = 0;
		}
		if (*str == ' ' && *flag == '0')
			word_begin = 1;
		str++;
		flag++;
	}
	return (word_counter);
}

static char	**ft_free_malloc(char **ptr, int j)
{
	while (--j >= 0)
		free(ptr[j]);
	free (ptr);
	return (0);
}

static int	splus(char *s, int i, char *flag)
{
	int	j;

	j = 0;
	while (s[i + j] == ' ' && flag[i + j] == '0')
		j++;
	return (j);
}

char	**expansion_split(char *s, char *flag)
{
	int		i;
	int		len;
	int		j;
	char	**ptr;

	j = 0;
	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (ft_word_count(s, flag) + 1));
	if (!ptr)
		return (NULL);
	ptr[ft_word_count(s, flag)] = NULL;
	i = 0;
	while (s[i])
	{
		len = 0;
		i += splus(s, i, flag);
		if (s[i] == '\0')
			return (ptr);
		while ((s[i + len] != ' ' && s[i + len]) || (flag[len + i] != '0' && flag[len + i] != '\0'))
			len++;
		ptr[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(ptr[j]))
			return (ft_free_malloc(ptr, j));
		ft_strlcpy(ptr[j], s + i, len + 1);
		j++;
		i += len;
	}
	ptr[j] = NULL;
	return (ptr);
}
