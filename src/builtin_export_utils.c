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

//returns 0 if just key
//returns 1 if key and equal sign
//returns 2 if key and equal sign and value
int	equal_sign_and_value(char *cmd1)
{
	int	i;

	i = 0;
	while (cmd1[i] != '\0' && cmd1[i] != '=')
		i++;
	if (cmd1[i] == '\0')
		return (0);
	if (cmd1[i] == '=' && cmd1[i + 1] == '\0')
		return (1);
	else
		return (2);
}

int	valid_var_check(char *new_var)
{
	int	i;

	i = 0;
	if (ft_strncmp(new_var, "=", 1) == 0
		|| ft_strncmp(new_var, ".", 1) == 0
		|| ft_isdigit(new_var[0]) == 1)
		return (FALSE);
	while (new_var[i] && new_var[i] != '=')
	{
		if (ft_isalnum(new_var[i]) != 1 && new_var[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	export_error_check(t_compound *cmds, char *new_var)
{
	int	flag;
	int	i;

	i = 0;
	flag = TRUE;
	if (valid_var_check(new_var) == FALSE)
	{
		flag = FALSE;
		print_error("export: ", new_var, "not a valid identifier");
		set_status(cmds, 1);
	}
	return (flag);
}

char	*save_key(char *cmd1)
{
	int		i;
	char	*key;

	key = NULL;
	i = 0;
	while (cmd1[i] != '=' && cmd1[i] != '\0')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (cmd1[i] != '=' && cmd1[i] != '\0')
	{
		key[i] = cmd1[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

//function is just called after a check whether a value exists
char	*save_value(char *cmd1)
{
	int		i;
	int		lenght_value;
	char	*value;

	value = NULL;
	i = 0;
	lenght_value = 0;
	while (cmd1[i] != '=' && cmd1[i] != '\0')
		i++;
	i++;
	while (cmd1[i + lenght_value] != '\0')
		lenght_value++;
	value = (char *)malloc(sizeof(char) * (lenght_value + 1));
	if (!value)
		return (NULL);
	lenght_value = 0;
	while (cmd1[i + lenght_value] != '\0')
	{
		value[lenght_value] = cmd1[i + lenght_value];
		lenght_value++;
	}
	value[lenght_value] = '\0';
	return (value);
}
