#include "woody.h"
#include "encrypt.h"

#define XOR(n) static void xor ##n (void *in, size_t in_len, uint ## n ##_t key) {\
		uint ##n##_t	*src;\
		src = (uint##n##_t *)in;\
		while (in_len >= n / 8)\
		{\
			*src ^= key;\
			in_len -= n / 8;\
			src++;\
		}\
	}

XOR(32)
XOR(16)
XOR(8)

//cpp src/encrypt/xor.c -I include/ -I libft/include/
 
void	xor(void *in, size_t in_len, uint32_t key, enum xor_size size)
{
	switch (size) {
		case X32:
			xor32(in, in_len, key);
			break;
		case X16:
			xor16(in, in_len, key);
			break;
		case X8:
			xor8(in, in_len, key);
			break;
	}
}

