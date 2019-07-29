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
	int		size_str;
	
	if ((size_str = (int)ft_strlen(key)) > (int)size * 2) {
		fprintf(stderr, "Warning !!! Given key to long it will be truncate\n"); 
	}
	size_t i = 0;
	size_t copy_size;
	do {
		copy_size = (size_str / 8) ? 8 : size_str;
		cast[i] = ft_atoi_base(key + (size_str - copy_size), "0123456789ABCDEF");
		key[size_str - copy_size] = 0;
		size_str -= copy_size;
		i++;
	} while (i < size / 4 && size_str > 0);
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
