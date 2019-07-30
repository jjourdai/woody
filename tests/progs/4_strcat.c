#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	char	*str;

	str = malloc(1024 * 1024);
	*str = 0;
	strcat(str, "je suis le debut d'une chaine de caracteres tres longue\n");

	for (int i = 0; i < 1000; ++i)
	{
		char	tmp[100];
		tmp[0] = 0;
		snprintf(tmp, 100, "Ligne %d\n", i);
		strcat(str, tmp);
	}
	strcat(str, "Je suis la fin d'une chaine de caracteres\n");
	printf("%s\n", str);
	return (0);
}
