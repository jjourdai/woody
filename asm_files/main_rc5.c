
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void		rc5(void *ptr, size_t ptr_len, uint8_t key[16], size_t nb_round);

int		main(void)
{
	uint8_t	key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	char	data[256];

	for(size_t i = 0; i < 256; ++i)
		data[i] = i;
	rc5(data, 256, key, 32);

	for (size_t i = 0; i < 256; ++i)
		printf("%02x ", data[i] & 0xFF);
	printf("\n");

	return (0);
}
