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
			else
				return (len + 1);
		}
		len++;
	}
	return (len);
}

char *token_creat(char *str, char **tokens)
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
	size_t	len;

	len = token_counter(str);
	tokens = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	tokens[len] = NULL;
	i = 0;
	while (*str)
	{			
		while(*str && (*str == ' ' || *str == '\t'))
			str++;
		if (*str)
		{	
			tokens[i] = token_creat(str, tokens);
			if (!tokens[i])
				return (NULL);
			len = token_lenght(str);
			if (str[0] == '>' && str[1] == '|')
				str++;
			str += len;
		}
		i++;
	}
	return (tokens);
}

char	**lexis(char *str)
{
	char	**tokens;
	size_t	nbr_token;

	nbr_token = token_counter(str);
	tokens = tokenizer(str);
	if (!tokens)
		return (NULL);
	return (tokens);
}