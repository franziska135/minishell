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

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>


typedef struct s_list
{
	char	**paths_split;
	char	*path;
	char	**envp;
	int		path_amt;
}	t_list;

void	split_envp_paths(t_list *m, char *envp[], char *str);
void	find_envp_path(t_list *m, char *str);
int		main(int argc, char *argv[], char *envp[]);
void	ft_pwd(t_list *m);

//libft
char	*ft_strdup(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len, int flag);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char *s1, char const *set);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif