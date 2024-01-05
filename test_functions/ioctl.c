#include "../minishell.h"

// the man page is not very informative. the job of ioctl is to control some aspects of the terminal.
// idk which aspects we need to control and our use of the fuction is depend on that.
// but here im gonna check for the terminal size and print it out. then wait 2 second, resize the terminal and exit.


int main()
{
	struct winsize	size;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1)
		perror(NULL);

	printf("Height :%d\tWidth: %d\n", size.ws_row, size.ws_col);
	sleep (2);
	size.ws_col = 100;
	size.ws_row = 100;

	if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &size) == -1)
        perror("NULL");
	printf("Height :%d\tWidth: %d\n", size.ws_row, size.ws_col);


}

/*
	as this code doesnt really change terminal size in my pc, i found this info:

	Note that changing the window size programmatically may not have an immediate effect in all cases,
	depending on the terminal emulator and its settings. Also, keep in mind that changing the window size
	from within a program is typically not recommended, as it can interfere with user preferences.
*/