#include "minishell.h"

static size_t	qout_counter(char *str)
{
	size_t	i;
	size_t	nbr_qouts;
	int		qout;

	i = 0;
	qout = 0;
	nbr_qouts = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && qout == 0)
		{
			qout = 1;
			nbr_qouts++;
		}
		else if (str[i] == '"' && qout == 0)
		{
			qout = 2;
			nbr_qouts++;
		}
		else if (str[i] == '\'' && qout == 1 || str[i] == '"' && qout == 2)
			qout = 0;
		i++;
	}
	return (nbr_qouts);
}

static int	shall_cpy(char *str, size_t i)
{
	if (str[i] != '"' && str[i] != '\'')
		return (TRUE);
	if (in_quot(str, i) && i == 0)
		return (FALSE);
	if (in_quot(str, i) != in_quot(str, i - 1))
		return (FALSE);
	return (TRUE);
}

char	*remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	*dst;
	int		nbr_qouts;

	nbr_qouts = qout_counter(str);
	dst = (char *)malloc(sizeof(char) * ft_strlen(str) - nbr_qouts);
	if (!dst)
		return (NULL);
	dst[ft_strlen(str) - nbr_qouts] = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (shall_cpy(str, i))
		{
			dst[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	return (dst);
}
