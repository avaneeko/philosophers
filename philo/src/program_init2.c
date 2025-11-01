/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:33:24 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:41:40 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//$ This file implements functions that populate the critical section and thread
// arrays, this initialization is self-contained, meaning it fully cleans up
// if there was an initialization failure.
//
// This is the second stage of the initialization, and it runs after the first.

static int	alloc_data(t_prog *p);
static int	init_criticals(t_prog *p);
static int	create_threads(t_prog *p);

static int	create_acq_or_fail(t_prog *p)
{
	unsigned int	i;

	if (pthread_mutex_init(&p->print_acq, NULL) != 0)
	{
		i = ~0;
		while (++i < p->n_philo)
			pthread_mutex_destroy(&p->forks[i]);
		null_free((void *[]){&p->philos, &p->th, &p->forks, NULL});
		return (0);
	}
	return (1);
}

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
		p->philos[i].l_fork = &p->forks[(i + 0) % p->n_philo];
		p->philos[i].r_fork = &p->forks[(i + 1) % p->n_philo];
		p->philos[i].n_eaten = 0;
		p->philos[i].last_meal = 0;
	}
	if (!init_criticals(p) || !create_threads(p) || !create_acq_or_fail(p))
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
				pthread_mutex_destroy(p->forks + k);
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
	unsigned int	i;
	unsigned int	k;

	i = ~0;
	while (++i < p->n_philo)
	{
		if (p->n_philo == 1)
			p->err = pthread_create(p->th, NULL, proc_single, p->philos + i);
		else
			p->err = pthread_create(p->th + i, NULL, proc, p->philos + i);
		if (p->err)
		{
			p->sim_stop = 1;
			p->s_barrier = 1;
			k = ~0;
			while (++k < i)
				pthread_join(p->th[k], NULL);
			null_free((void *[]){&p->philos, &p->th, &p->forks, NULL});
			return (0);
		}
	}
	return (1);
}
