#include "philo.h"

//$ This file defines a function that logs the state of the simulation.
// It always prints a timestamp, number of the philosopher and predefined msg.

unsigned long	now_ms(void);

// This assumes out_size points to an initialized value.
unsigned	ultostr(unsigned long n, char *s)
{
	unsigned int	i;

	if (n == 0)
		return (s[0] = '0') == '0';
	i = 0;
	while (n)
	{
		s[i++] = "0123456789"[n % 10];
		n /= 10;
	}
	mreverse(s, i);
	return (i);
}

// id - philosophers id (not number!!!)
// msg - message from the MSG_* defines.
void	log_state(unsigned int id, char const *msg, _Atomic int const *sim_end)
{
	char			buf[LOG_BUF_SIZE];
	unsigned int	i;

	i = 0;
	i += ultostr(now_ms(), buf);
	buf[i++] = ' ';
	i += ultostr(id + 1, buf + i);
	buf[i++] = ' ';
	mcpy(buf + i, msg, slen(msg));
	i += slen(msg);
	if (!*sim_end)
		write(STDOUT_FILENO, buf, i);
}

// REVISED LOCAL
extern unsigned long START;
unsigned long	now_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return 0;
	return ((unsigned long)tv.tv_sec * 1000u + (unsigned long)tv.tv_usec / 1000u) - START;
}

// Current timestamp in ms.
// unsigned long	now_ms(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL) != 0)
// 		return 0;
// 	return (unsigned long)tv.tv_sec * 1000u + (unsigned long)tv.tv_usec / 1000u;
// }
