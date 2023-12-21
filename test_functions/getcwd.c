#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
int	main()
{
	char	*ret;
	char	buf;

	buf = NULL;		//if buffer is NULL getcwd() allocate it atomatically, if not we have to allocate it, otherwise many memorry errors
	ret = getcwd(buf, 10);
	perror(NULL); 
	if (!ret)
		ret = getcwd(buf, 0);
	printf("ret: {%s}\nbuf: {%s}\n", ret, buf);
	free(ret);
}*/
//SECOND IMPLEMENTATION
int main()
{
	char	buf[100];

	if (getcwd(buf, 100) != NULL)
		printf("buf: %s\n", buf);
	else
		perror(NULL);
}

