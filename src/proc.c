#include "philo.h"
#include <unistd.h>

//$ This file defines an entry procedure of each thread.

int	sim(t_philo *p);

void	*proc(void *arg)
{
	t_philo *const	p = (t_philo *)arg;

	// Wait for all threads to be created.
	while (p->prog->s_barrier == 0)
		;
	while (p->prog->sim_stop == 0)
	{
		log_state(p->id, MSG_THINKING, &p->prog->sim_stop);
		sim(p);
		log_state(p->id, MSG_SLEEPING, &p->prog->sim_stop);
		sleep_aware(p->prog->t_sleep * 1000, &p->prog->sim_stop);
	}
	return (NULL);
}

int	sim(t_philo *p)
{
	if (p->id & 1)
	{
		// Odd.
		pthread_mutex_lock(p->l_fork);
		log_state(p->id, MSG_TAKEN_FORK, &p->prog->sim_stop);
		pthread_mutex_lock(p->r_fork);
		log_state(p->id, MSG_TAKEN_FORK, &p->prog->sim_stop);
	}
	else
	{
		// Even.
		pthread_mutex_lock(p->r_fork);
		log_state(p->id, MSG_TAKEN_FORK, &p->prog->sim_stop);
		pthread_mutex_lock(p->l_fork);
		log_state(p->id, MSG_TAKEN_FORK, &p->prog->sim_stop);
	}
	p->last_meal = now_ms();
	log_state(p->id, MSG_EATING, &p->prog->sim_stop);
	if (p->prog->n_to_eat != ~0u)
		p->n_eaten++;
	sleep_aware(p->prog->t_eat * 1000, &p->prog->sim_stop);
	if (p->id & 1)
	{
		// Odd.
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
	}
	else
	{
		// Even.
		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(p->l_fork);
	}
	return (0);
}