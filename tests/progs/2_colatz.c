#include <stdio.h>
#include <stdint.h>

static void		collatz(uint32_t i)
{
	printf("%d\n", i);
	if (i <= 1)
		return ;
	if (i % 2 == 0)
		collatz(i / 2);
	else
		collatz(i * 3 + 1);
}

int				main(void)
{
	collatz(1);
	collatz(17);
	collatz(25);
	collatz(42);
	collatz(400);
	collatz(2000);
	collatz(4000);
	collatz(1024);
}
