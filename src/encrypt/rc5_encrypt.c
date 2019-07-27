#include "encrypt.h"
#include "libft.h"

static void	init_S_array(uint64_t S[S_SIZE], uint8_t random_key[KEY_SIZE])
{
	uint64_t	L[L_SIZE];
	int			tmp[3];
	size_t		reg[2];

	S[0] = P;
	for (size_t i = 1; i < S_SIZE; ++i)
		S[i] = S[i - 1] + Q;
	for (size_t i = 0; i < L_SIZE; ++i)
		L[i] = 0;
	for (size_t i = 0; i < KEY_SIZE; ++i)
	{
		tmp[0] = random_key[i] << (8 * (i % 4));
		L[i / 8] += tmp[0];
	}
	tmp[0] = 3 * ((S_SIZE < L_SIZE) ? L_SIZE : S_SIZE);
	tmp[1] = 0;
	tmp[2] = 0;
	reg[0] = 0;
	reg[1] = 0;
	while (tmp[0]-- > 0)
	{
		reg[0] = ROTL(S[tmp[1]] + reg[0] + reg[1], 3);
		S[tmp[1]] = reg[0];
		reg[1] = ROTL(L[tmp[2]] + reg[0] + reg[1], reg[0] + reg[1]);
		L[tmp[2]] = reg[1];
		tmp[1] = (tmp[1] + 1) % S_SIZE;
		tmp[2]++;
		tmp[2] %= L_SIZE;
	}
}

static void	cipher(uint64_t S[S_SIZE], uint64_t *AA, uint64_t *BB)
{
	uint64_t	A;
	uint64_t	B;

	A = *AA;
	B = *BB;

	A += S[0];
	B += S[1];

	for (size_t i = 1; i <= NB_ROUNDS; ++i)
	{
		A = A ^ B;
		A = ROTL(A, B) + S[2 * i];
		B = B ^ A;
		B = ROTL(B, A) + S[2 * i + 1];
	}

	// uncipher

	// for (size_t i = NB_ROUNDS; i >= 1; --i)
	// {
	// 	B = B - S[2 * i + 1];
	// 	B = ROTR(B, A) ^ A;
	// 	A = A - S[2 * i];
	// 	A = ROTR(A, B) ^ B;
	// }

	// A -= S[0];
	// B -= S[1];

	*AA = A;
	*BB = B;
}

void		rc5_encrypt(void *in, size_t in_len, uint8_t key[KEY_SIZE])
{
	uint64_t	S[S_SIZE];
	uint64_t	*src;

	init_S_array(S, key);

	src = (uint64_t *)in;
	while (in_len >= 16)
	{
		cipher(S, src + 0, src + 1);
		src += 2;
		in_len -= 16;
	}
}
