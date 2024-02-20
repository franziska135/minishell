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
#include <stdio.h>

int	main(void)
{
	char	buf[100];

	printf("%s\n", getcwd(buf, 100));
	//-1 is error and 0 is working
	if (chdir("../../") == -1)
		perror(NULL);
	// chdir(buf);		//to go back to where it was
	printf("%s\n", getcwd(buf, 100));
}
