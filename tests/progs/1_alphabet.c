#include <stdio.h>

int		main(void)
{
	char		alphabet[27];

	alphabet[26] = 0;
	for (size_t i = 0; i < 26; ++i)
		alphabet[i] = 'a' + i;
	printf("%s\n", alphabet);
	for (size_t i = 0; i < 26; ++i)
		alphabet[i] = 'A' + i;
	printf("%s\n", alphabet);
}
