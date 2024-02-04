// #include "minishell.h"

// static int	ft_word_counter(char *str, char c)
// {
// 	int	word_counter;
// 	int	word_begin;

// 	word_begin = 1;
// 	word_counter = 0;
// 	while (*str)
// 	{
// 		if (word_begin == 1 && *str != c && !in_quot(str, 0))
// 		{
// 			word_counter++;
// 			word_begin = 0;
// 		}
// 		else if (*str == c && !in_quot(str, 0))
// 			word_begin = 1;
// 		str++;
// 	}
// 	return (word_counter);
// }

// static char	**ft_free_malloc(char **ptr, int j)
// {
// 	while (--j >= 0)
// 		free(ptr[j]);
// 	free (ptr);
// 	return (0);
// }

// static int	s_plus(char *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] == c && !in_quot(s, i))
// 		i++;
// 	return (i);
// }

// char	**ft_new_split(char *s)
// {
// 	int		i;
// 	int		j;
// 	char	**ptr;

// 	j = 0;
// 	ptr = (char **)malloc(sizeof(char *) * (ft_word_counter(s, c) + 1));
// 	if (!ptr)
// 		return (0);
// 	ptr[ft_word_counter(s, ' ')] = NULL;
// 	while (*s)
// 	{
// 		i = 0;
// 		s += s_plus(s, ' ');
// 		if (*s == '\0')
// 			return (ptr);
// 		while (s[i] && s[i] != c && !in_quot(s, i))
// 			i++;
// 		ptr[j] = (char *)malloc(sizeof(char) * (i + 1));
// 		if (!(ptr[j]))
// 			return (ft_free_malloc(ptr, j));
// 		ft_strlcpy(ptr[j], s, i + 1);
// 		j++;
// 		s += i;
// 	}
// 	return (ptr);
// }
