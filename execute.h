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
#define ECHO 2
#define CD 3
#define PWD 4
#define EXPORT 5
#define UNSET 6
#define ENV 7
#define B_EXIT 8

typedef struct s_path
{
	char	**binary_paths;
	int		amt_children;
	int		amt_pipes;
}	t_list;

//initialize and error messages
void	init_path_struct(t_list *execute);
void	print_error(char *str1, char *str2, char *str3, char *str4);


//PATH paths
// void		init_path_struct(t_list *binarypaths);
void		split_binary_paths(t_list *execute, t_compound *compound);
//can be taken out at some point:
void		print_paths(t_list *execute);

//check amt of commands and pipes, children
void		tweak_simple_commands(t_list *execute, t_compound *compound);
void		flag_builtins(t_simple **cmd);
void		process_commands(t_list *execute, t_compound *compound);
void		execute_builtin(t_simple *simple_command);

//builtins
void		builtin_pwd(void);
void		builtin_cd(t_simple *simple_command);

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
size_t		ft_strlen(const char *str);


#endif