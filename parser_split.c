#include "minishell.h"

static int	ft_word_count(char *str)
{
	int	word_counter;
	int	word_begin;
	int	quotes;

	word_begin = 1;
	word_counter = 0;
	quotes = 0;
	while (*str)
	{
		if (word_begin == 1 && *str != ' ' && quotes == 0)
		{
			word_counter++;
			word_begin = 0;
		}
		else if (*str == ' ' && quotes == 0)
			word_begin = 1;
		else if (*str == '"' && quotes == 0)
			quotes = 1;
		else if (*str == '"' && quotes == 1)
			quotes = 0;
		str++;
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

static int	splus(char *s, int i)
{
	int	j;

	j = 0;
	while (s[i + j] == ' ' && !in_quot(s, i + j))
		j++;
	return (j);
}

char	**expansion_split(char *s)
{
	int		i;
	int		len;
	int		j;
	char	**ptr;

	j = 0;
	if (!s)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (ft_word_count(s) + 1));
	if (!ptr)
		return (NULL);
	ptr[ft_word_count(s)] = NULL;
	i = 0;
	while (s[i])
	{
		len = 0;
		i += splus(s, i);
		if (s[i] == '\0')
			return (ptr);
		while ((s[i + len] != ' ' && s[i + len]) || in_quot(s, len + i))
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


// int main()
// {
// 	char *str = NULL;
// 	char **split = expansion_split(str);

// 	int i = 0;
// 	while (split && split[i])
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// 	printf("%s\n", split[i]);
// }