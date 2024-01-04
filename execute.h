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

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <stdlib.h>

typedef struct s_path
{
	char	**paths;
}	t_path;

//PATH paths
// void		init_path_struct(t_path *binarypaths);
void		split_binary_paths(t_path *binarypaths, t_compound *compound);
//can be taken out at some point:
void		print_paths(t_path *binarypaths);

//cleaning up at error
void		cleanup(t_path *binarypath, t_compound *compound);
void		free_double_ptr(char **double_ptr);
void		free_list(t_simple **cmd);

//utils identical to the libft folder and can be removed once linked
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
static int	ft_word_counter(char const *str, char c);
static char	**ft_free_malloc(char **ptr, int j);
static int	s_plus(const char *s, char c);
char		**ft_split(char const *s, char c);

#endif