#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

//COMPILE:	cc stat.c ../libft/*.c
int main()
{
	char	buf[100];
	char	*path;
	getcwd(buf, 100);
	path = ft_strjoin(buf, "/stat.c");

}