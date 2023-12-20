#include <unistd.h>
#include <stdio.h>

int main()
{
	char	buf[100];
	
	printf("%s\n", getcwd(buf, 100));
	if (chdir("../../") == -1) //-1 is error and 0 is working
		perror(NULL);
	// chdir(buf);		//to go back to where it was
	printf("%s\n", getcwd(buf, 100));
}