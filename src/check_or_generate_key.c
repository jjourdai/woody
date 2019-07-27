#include "woody.h"
#include "colors.h"

static void 	get_random_data(void *buffer, size_t size)
{
	int		fd;

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		exit(fd);
	read(fd, buffer, size);
	close(fd);
	return ;
}

static void	atoi_key(void *data, size_t size, char *key)
{
	uint32_t	*cast = data;
	size_t		size_str;
	
	if ((size_str = ft_strlen(key)) > size * 2) {
		fprintf(stderr, "Warning !!! Given key to long it will be truncate\n"); 
	}
	size_str = (size_str >= 8) ? size_str - 8 : 0;
	size_t i = 0;
	do {
		cast[i] = ft_atoi_base(key + size_str, "0123456789ABCDEF");
		key[size_str] = 0;
		i++;
		size_str -= 8;
	} while (i < size / 4);
}

void	verify_key(void *data, size_t size)
{
	if (g_env.flag.value & F_KEY) {
		atoi_key(data, size, g_env.flag.key_str);
	} else {
		get_random_data(data, size);
	}
	printf(RED_TEXT("Encryption key : '0x"));
	size_t i = 0;
	do {
		printf(RED_TEXT("%hhx"), ((uint8_t*)data)[i]);
	} while (++i < size);
	printf(RED_TEXT("'\n"));
}