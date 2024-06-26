/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:57:20 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 16:57:26 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	token_lenght(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
	{
		if (!in_quot(str, len) && is_delimiter(str[len]))
		{
			if (str[len] == ' ' || str[len] == '\t')
				return (len);
			else if (len == 0 && str[len] == str[len + 1])
				return (2);
			else if (len == 0)
				return (1);
			else
				return (len);
		}
		len++;
	}
	return (len);
}

char	*token_creat(char *str, char **tokens)
{
	char	*token;
	size_t	len;

	len = token_lenght(str);
	token = (char *)malloc(sizeof(char) * len + 1);
	if (!token)
		return (dpointer_free(tokens), NULL);
	ft_strlcpy(token, str, len + 1);
	return (token);
}

static char	**tokenizer(char *str)
{
	char	**tokens;
	size_t	i;

	tokens = (char **)malloc(sizeof(char *) * (token_counter(str) + 1));
	if (!tokens)
		return (NULL);
	tokens[token_counter(str)] = NULL;
	i = 0;
	while (*str)
	{
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		if (*str)
		{
			tokens[i] = token_creat(str, tokens);
			if (!tokens[i])
				return (NULL);
			if (str[0] == '>' && str[1] == '|')
				str++;
			str += token_lenght(str);
		}
		i++;
	}
	return (tokens);
}

char	**lexis(char *str)
{
	char	**tokens;

	tokens = tokenizer(str);
	free (str);
	if (!tokens)
		return (NULL);
	return (tokens);
}
