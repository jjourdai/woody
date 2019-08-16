#include "encrypt.h"
#include "libft.h"

#define SIZE_PERMUTATION 256

uint8_t		*init_s_permutation_tab(uint8_t key[KEY_SIZE])
{
	static uint8_t	S[SIZE_PERMUTATION] = {0};
	uint8_t		swap;
	uint8_t		j;
	int		i;

	for (i = 0; i < SIZE_PERMUTATION; i++) {
		S[i] = i;
	}
	for (j = 0, i = 0;  i < SIZE_PERMUTATION; i++) {
		j = (j + S[i] + key[i % KEY_SIZE]) % SIZE_PERMUTATION;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}
/*
	printf("\n");
	printf("KEY STREAM :\n");
	for (int i = 0; i < SIZE_PERMUTATION; i++) {
		printf("%hhx ", S[i]);
	}
	printf("\n");
*/
	return S;
}


void		rc4_encrypt(void *in, size_t in_len, uint8_t key[KEY_SIZE])
{
	uint8_t *S, *data;
	int	i, j;
	size_t	length;
	uint8_t swap, cipher_byte;

	S = init_s_permutation_tab(key);
	data = (uint8_t*)in;
	
	i = 0;
	j = 0;
	for (length = 0; length < in_len; length++) {
		i = (i + 1) % SIZE_PERMUTATION;	
		j = (j + S[i]) % SIZE_PERMUTATION;

		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
		cipher_byte = S[(S[i] + S[j]) % SIZE_PERMUTATION];
		data[length] = cipher_byte ^ data[length];
	}
/*
	//DECRYPT
	S = init_s_permutation_tab(key);
	i = 0;
	j = 0;
	for (length = 0; length < in_len; length++) {
		i = (i + 1) % SIZE_PERMUTATION;	
		j = (j + S[i]) % SIZE_PERMUTATION;

		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
		cipher_byte = S[(S[i] + S[j]) % SIZE_PERMUTATION];
		data[length] = cipher_byte ^ data[length];
	}
*/
/*
	printf("PRINT : \n");
	for (i = 0; i < in_len; i++) {
		printf("%hhx", data[i]);
	}
	printf("\n");
*/
}
