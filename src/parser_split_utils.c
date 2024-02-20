/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:13:33 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:13:35 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_count(char *str, char *flag)
{
	int	word_counter;
	int	word_begin;

	word_begin = 1;
	word_counter = 0;
	while (*str)
	{
		if (*flag == '3')
		{
			word_counter++;
			word_begin = 1;
		}
		else if ((word_begin == 1 && *str != ' ')
			|| (word_begin == 1 && *flag != '0'))
		{
			word_counter++;
			word_begin = 0;
		}
		else if (*str == ' ' && *flag == '0')
			word_begin = 1;
		str++;
		flag++;
	}
	return (word_counter);
}

char	*create_str(char *s, int *i, int len, char flag)
{
	char	*ptr;

	if (flag == '3')
	{
		ptr = (char *)malloc(sizeof(char));
		if (!(ptr))
			return (NULL);
		ptr[0] = '\0';
		*i += 1;
	}
	else
	{
		ptr = (char *)malloc(sizeof(char) * (len + 1));
		if (!(ptr))
			return (NULL);
		ft_strlcpy(ptr, s + *i, len + 1);
		*i += len;
	}
	return (ptr);
}
