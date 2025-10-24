#include "philo.h"

//$ This file implements functions that populate the critical section and thread
// arrays, this initialization is self-contained, meaning it fully cleans up
// if there was an initialization failure.
//
// This is the second stage of the initialization, and it runs after the first.

static int	alloc_data(t_prog *p);
static int	init_criticals(t_prog *p);
static int	create_threads(t_prog *p);

// Allocate simulation resources: critical sections and threads.
// Returns 0 on failure.
int	alloc_simulation(t_prog *p)
{
	unsigned int	i;

	if (!alloc_data(p))
		return (0);
	i = ~0;
	while (++i < p->n_philo)
	{
		p->philos[i].id = i;
		p->philos[i].prog = p;
		p->philos[i].l_fork = &p->forks[(i - 1) % p->n_philo];
		p->philos[i].r_fork = &p->forks[(i + 1) % p->n_philo];
		p->philos[i].n_eaten = 0;
		p->philos[i].last_meal = 0;
	}
	if (!init_criticals(p) || !create_threads(p))
		return (0);
	return (1);
}

// Allocates memory for p->philos p->th and p->forks
static int	alloc_data(t_prog *p)
{
	p->philos = malloc(sizeof(t_philo) * p->n_philo);
	p->th = malloc(sizeof(t_thread) * p->n_philo);
	p->forks = malloc(sizeof(t_critical) * p->n_philo);
	if (!p->philos || !p->th || !p->forks)
	{
		free(p->philos);
		free(p->th);
		free(p->forks);
		p->philos = 0;
		p->th = 0;
		p->forks = 0;
		p->err = ENOMEM;
		return (0);
	}
	return (1);
}

// Initializes all critical sections (forks).
// Returns 0 on failure and frees allocated data.
static int	init_criticals(t_prog *p)
{
	unsigned int	i;
	unsigned int	k;

	i = ~0;
	while (++i < p->n_philo)
	{
		p->err = pthread_mutex_init(p->forks + i, NULL);
		if (p->err)
		{
			k = ~0;
			while (++k < i)
				pthread_mutex_destroy(p->forks + i);
			free(p->philos);
			free(p->th);
			free(p->forks);
			p->philos = 0;
			p->th = 0;
			p->forks = 0;
			return (0);
		}
	}
	return (1);
}

static int	create_threads(t_prog *p)
{
	unsigned int	i = 0;
	// TODO
	return (1);
}