#include "philo.h"

//$ This file defines an entry procedure of each thread.

void	*proc(void *arg)
{
	t_philo *const	self = (t_philo *)arg;

	// Wait for all threads to be created.
	while (self->prog->s_barrier == 0)
		usleep(100);
	while (self->prog->sim_stop == 0)
	{
		usleep(100);
	}
	return (NULL);
}