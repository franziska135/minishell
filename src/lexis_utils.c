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

static size_t	token_parse(char **str, int i, int *word_begin)
{
	size_t	word_count;

	word_count = 0;
	if (str[0][i] == ' ' || str[0][i] == '\t')
		*word_begin = 0;
	else if (is_delimiter(str[0][i]))
	{
		if (str[0][i] == '>' && str[0][i + 1] == '|')
			i++;
		word_count++;
		*word_begin = 0;
		if (str[0][i] == str[0][i + 1])
			str[0] += 1;
	}
	else if (*word_begin == 0)
	{
		word_count++;
		*word_begin = 1;
	}
	return (word_count);
}

size_t	token_counter(char *str)
{
	size_t	word_count;
	int		i;
	int		word_begin;

	word_begin = 0;
	i = 0;
	word_count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!in_quot(str, i))
			word_count += token_parse(&str, i, &word_begin);
		if (str[i] == '>' && str[i + 1] == '|')
			i++;
		i++;
	}
	return (word_count);
}
