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

size_t	ft_strlen(const char *s)
{
	int		i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;
	int		size;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > 0 && ft_strchr(set, s1[end]))
		end--;
	size = end - start + 1;
	if (start > end)
		size = 1;
	result = (ft_substr(s1, start, (size), 0));
	if (!result)
		return (NULL);
	//free(s1);
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int flag)
{
	unsigned int	i;
	char			*p_string;
	size_t			length;

	i = 0;
	length = 0;
	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	if (len < length)
		length = len;
	p_string = (char *)malloc(sizeof(char) * (length + 1 + flag));
	if (p_string == NULL)
		return (NULL);
	while (i < length && s[start + i] != '\0')
	{
		p_string[i] = s[start + i];
		i++;
	}
	if (flag == 1)
		p_string[i] = '/';
	p_string[i + flag] = '\0';
	return (p_string);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*p_newstr;

	i = 0;
	while (s[i] != '\0')
		i++;
	p_newstr = (char *)malloc((i + 1) * sizeof(char));
	if (p_newstr == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		p_newstr[i] = s[i];
		i++;
	}
	p_newstr[i] = '\0';
	return (p_newstr);
}
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	else if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else
		return (0);
}