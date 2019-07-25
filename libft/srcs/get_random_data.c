char *get_random_data()
{
	int			fd;
	char	*buffer;

	buffer = malloc (512);
	if ((fd = open("/dev/random", O_RDONLY)) == -1)
		exit(fd);
	read(fd, buffer, 128);
	close(fd);
	return (buffer);
}
