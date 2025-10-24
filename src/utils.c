#include "philo.h"

size_t	slen(char const *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

// Print a string to fd
static int	print_fd(int fd, char const *s)
{
	size_t const	len = slen(s);
	ssize_t const	written = write(fd, s, len);

	return ((size_t)written == len);
}

int	print(char const *s)
{
	return (print_fd(STDOUT_FILENO, s));
}

int	print_err(char const *s)
{
	return (print_fd(STDERR_FILENO, s));
}

void	null_free(void *p[])
{
	while (*p)
	{
		free(*(void **)*p);
		*(void **)*p = 0;
		p++;
	}
}