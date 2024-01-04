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

#define TRUE 1
#define FALSE 0

typedef struct s_path
{
	char	**binary_paths;
	int		amt_children;
	int		amt_pipes;
}	t_list;

//initialize struct members
void	init_path_struct(t_list *execute);

//PATH paths
// void		init_path_struct(t_list *binarypaths);
void		split_binary_paths(t_list *execute, t_compound *compound);
//can be taken out at some point:
void		print_paths(t_list *execute);

//check amt of commands and pipes, children
void		process_commands(t_list *execute, t_compound *compound);
void		flag_builtins(t_simple **cmd);

//cleaning up at error
void		cleanup(t_list *execute, t_compound *compound);
void		free_double_ptr(char **double_ptr);
void		free_list(t_simple **cmd);

//utils identical to the libft folder and can be removed once linked
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
static int	ft_word_counter(char const *str, char c);
static char	**ft_free_malloc(char **ptr, int j);
static int	s_plus(const char *s, char c);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif