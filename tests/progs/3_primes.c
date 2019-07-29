#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static int		is_prime(uint32_t p)
{
	for (size_t i = 2; i * i < p; i += (i % 2 == 0) ? 1 : 2) {
		if (p % i == 0)
			return (0);
	}
	return (1);
}

#define STR_OF_BOOL(b)	((b) ? "TRUE" : "FALSE")

static void		test(uint32_t n)
{
	int		prime;

	prime = is_prime(n);
	printf("n: %d, is_prime: %s\n", n, STR_OF_BOOL(prime));
}

int				main(void)
{
	for (size_t i = 2; i < 1000; ++i)
		test(i);
	return (0);
}
