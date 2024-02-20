/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:13:56 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**init_split(char *s, char *flag, int *i, int *j)
{
	char	**ptr;

	*j = 0;
	*i = 0;
	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (ft_word_count(s, flag) + 1));
	if (!ptr)
		return (NULL);
	ptr[ft_word_count(s, flag)] = NULL;
	return (ptr);
}

char	**expansion_split(char *s, char *flag)
{
	int		i;
	int		len;
	int		j;
	char	**ptr;

	ptr = init_split(s, flag, &i, &j);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		len = 0;
		i += splus(s, i, flag);
		while ((s[i + len] != ' ' && s[i + len])
			|| (flag[len + i] != '0' && flag[len + i] != '\0'))
			len++;
		if (s[i] == '\0')
			return (ptr);
		ptr[j] = create_str(s, &i, len, flag[i]);
		if (!(ptr[j]))
			return (ft_free_malloc(ptr, j));
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}
