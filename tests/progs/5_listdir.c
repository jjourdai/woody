#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main (void)
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir ("./src");

	if (dp != NULL)
	{
		while ((ep = readdir (dp)) != NULL)
			puts (ep->d_name);

	(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");

	return 0;
}
