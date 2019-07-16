#include "libft.h"

uint16_t	compute_checksum(void *data, size_t size)
{
	size_t		i;
	uint32_t	result;
	uint16_t	*ptr;

	i = -1;
	size = size / 2; //to work on 16 bytes
	result = 0;
	ptr = (uint16_t*)data;
	while (++i < size)
		result += ptr[i];
	if (0xffff0000 & result) {
		result = (result & 0xffff) + ((0xffff0000 & result) >> 16);
	}
	return (uint16_t)(~result);
}
