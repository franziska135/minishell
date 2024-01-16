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


#define TRUE 1
#define FALSE 0
#define ECHO 2
#define CD 3
#define PWD 4
#define EXPORT 5
#define UNSET 6
#define ENV 7
#define B_EXIT 8

typedef struct s_execute
{
	char	**binary_paths;
	int		amt_children;
	int		amt_pipes;
}	t_execute;

//initialize and error messages
void		init_path_struct(t_execute *execute);
void		print_error(char *str1, char *str2, char *str3, char *str4);

//node stuff
void		init_env_llist(t_compound *cmds, char **envp);
//can eventually be taken out
void		free_node(void *node);
t_env		*find_node(t_compound *cmds, char *needle);
//adjusted libft lstnew
t_env		*ft_new_env_node(char *key, char *value);
//adjusted lstaddback libft
void		ft_add_last_node(t_env **lst, t_env *new);

//PATH paths
// void		init_path_struct(t_env *binarypaths);
void		split_binary_paths(t_execute *execute, t_compound *compound);
//can be taken out at some point:
void		print_paths(t_execute *execute);

//check amt of commands and pipes, children
void		tweak_simple_commands(t_execute *execute, t_compound *compound);
void		flag_builtins(t_compound *cmds);
void		process_commands(t_execute *execute, t_compound *compound);
void		execute_builtin(t_compound *compound, t_simple *simple_command);

//builtins
void		builtin_pwd(void);
void		builtin_cd(t_simple *simple_command, t_compound *cmds);
void		builtin_cd_home(t_compound *cmds);
void		builtin_cd_dotdot(t_compound *cmds);
void		builtin_cd_back(t_compound *cmds);
void    	builtin_cd_path(t_compound *cmds, t_simple *scmd);
void		update_env_ll(t_compound *cmds, char *variable, char *new_value);
void		builtin_env(t_env *head);
void		builtin_echo(t_simple *s_cmd);
int			check_for_n(t_simple *s_cmd);
int			check_for_only_n(char *str);
void		builtin_echo_write(t_simple *s_cmd, int i);
void		builtin_unset(t_compound *cmds, t_simple *scmd);
// int			ft_check_unset_variable(char *variable);


//cleaning up at error
void		cleanup(t_execute *execute, t_compound *compound);
void		free_double_ptr(char **double_ptr);
void		free_env(t_simple **cmd);
void		ft_free_list(t_env *lst);

//utils identical to the libft folder and can be removed once linked
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
static int	ft_word_counter(char const *str, char c);
static char	**ft_free_malloc(char **ptr, int j);
static int	s_plus(const char *s, char c);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);

#endif