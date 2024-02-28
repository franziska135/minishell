/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 18:14:39 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

int	in_quot(char *str, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (str && str[i] && i <= n)
	{
		if (str[i] == '\'' && res != 2)
		{
			if (res == 1)
				res = 0;
			else
				res = 1;
		}
		if (str[i] == '"' && res != 1)
		{
			if (res == 2)
				res = 0;
			else
				res = 2;
		}
		i++;
	}
	return (res);
}
