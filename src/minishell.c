/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <zolfagharipour@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:12:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/02/20 16:58:10 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **envp)
{
	t_compound	cmds;

	(void)av;
	(void)ac;
	if (init_env_llist(&cmds, envp) == FALSE)
		return (FALSE);
	run_minishell(&cmds);
	cleanup_envp_ll(cmds.env_ll);
	free_double_ptr(cmds.envp);
	return (WEXITSTATUS(cmds.exit_status));
}
