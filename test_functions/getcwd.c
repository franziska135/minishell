/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:22 by fmarggra          #+#    #+#             */
/*   Updated: 2024/02/01 14:24:16 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
int	main()
{
	char	*ret;
	char	buf;
	buf = NULL;		//if buffer is NULL getcwd() allocate it atomatically, 
	if not we have to allocate it, otherwise many memorry errors
	ret = getcwd(buf, 10);
	perror(NULL); 
	if (!ret)
		ret = getcwd(buf, 0);
	printf("ret: {%s}\nbuf: {%s}\n", ret, buf);
	free(ret);
}*/
//SECOND IMPLEMENTATION
int	main(void)
{
	char	buf[100];

	if (getcwd(buf, 100) != NULL)
		printf("buf: %s\n", buf);
	else
		perror(NULL);
}
