#include "philo.h"

//$ This file defines a function that logs the state of the simulation.
// It always prints a timestamp, number of the philosopher and predefined msg.

unsigned long	now_ms(unsigned long start_time);

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
void	log_state(t_philo *p, char const *msg)
{
	char			buf[LOG_BUF_SIZE];
	unsigned int	i;

	i = 0;
	i += ultostr(now_ms(p->prog->start_time), buf);
	buf[i++] = ' ';
	i += ultostr(p->id + 1, buf + i);
	buf[i++] = ' ';
	mcpy(buf + i, msg, slen(msg));
	i += slen(msg);
	pthread_mutex_lock(&p->prog->print_acq);
	if (!p->prog->sim_stop)
	{
		write(STDOUT_FILENO, buf, i);
		pthread_mutex_unlock((void *)&p->prog->print_acq);
		return ;
	}
	pthread_mutex_unlock(&p->prog->print_acq);
}

void	log_state_no_critical(t_philo *p, char const *msg)
{
	char			buf[LOG_BUF_SIZE];
	unsigned int	i;

	i = 0;
	i += ultostr(now_ms(p->prog->start_time), buf);
	buf[i++] = ' ';
	i += ultostr(p->id + 1, buf + i);
	buf[i++] = ' ';
	mcpy(buf + i, msg, slen(msg));
	i += slen(msg);
	if (!p->prog->sim_stop)
		write(STDOUT_FILENO, buf, i);
}

// REVISED LOCAL
unsigned long	now_ms(unsigned long start_time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return 0;
	return ((unsigned long)tv.tv_sec * 1000u
		+ (unsigned long)tv.tv_usec / 1000u) - start_time;
}

// Current timestamp in ms.
// unsigned long	now_ms(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL) != 0)
// 		return 0;
// 	return (unsigned long)tv.tv_sec * 1000u + (unsigned long)tv.tv_usec / 1000u;
// }
