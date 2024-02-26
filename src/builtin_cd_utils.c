/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/20 16:25:43 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error_check(t_simple *scmd)
{
	if (scmd->cmd[1] != NULL && scmd->cmd[2])
	{
		print_error("cd: ", NULL, "too many arguments");
		return (FALSE);
	}
	return (TRUE);
}

int	go_back_home(t_simple *scmd)
{
	if (scmd->cmd[1] == NULL)
		return (TRUE);
	else if (ft_strncmp(scmd->cmd[1], "~", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(scmd->cmd[1], "--", 3) == 0)
		return (TRUE);
	return (FALSE);
}
