#include "woody.h"

void	xor32(void *in, size_t in_len, uint32_t key)
{
	uint32_t	*src;

	src = (uint32_t *)in;
	while (in_len >= 4)
	{
		*src ^= key;
		in_len -= 4;
		src++;
	}
}
