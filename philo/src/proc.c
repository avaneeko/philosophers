/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:32:14 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:40:49 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

//$ This file defines an entry procedure of each thread.

int	sim(t_philo *p);

void	*proc(void *arg)
{
	t_philo *const	p = (t_philo *)arg;

	while (p->prog->s_barrier == 0)
		;
	if (p->id % 2 == 1)
		usleep(p->prog->t_eat * 1000 / 2);
	while (p->prog->sim_stop == 0)
	{
		log_state(p, MSG_THINKING);
		sim(p);
		log_state(p, MSG_SLEEPING);
		sleep_aware(p->prog->t_sleep * 1000, &p->prog->sim_stop);
		usleep(1000);
	}
	return (NULL);
}

int	sim(t_philo *p)
{
	if (p->id & 1)
	{
		pthread_mutex_lock(p->l_fork);
		log_state(p, MSG_TAKEN_FORK);
		pthread_mutex_lock(p->r_fork);
		log_state(p, MSG_TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(p->r_fork);
		log_state(p, MSG_TAKEN_FORK);
		pthread_mutex_lock(p->l_fork);
		log_state(p, MSG_TAKEN_FORK);
	}
	p->last_meal = now_ms(p->prog->start_time);
	log_state(p, MSG_EATING);
	if (p->prog->n_to_eat != ~0u)
		p->n_eaten++;
	sleep_aware(p->prog->t_eat * 1000, &p->prog->sim_stop);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	return (0);
}

void	*proc_single(void *arg)
{
	t_philo *const	p = (t_philo *)arg;

	log_state(p, MSG_THINKING);
	pthread_mutex_lock(p->l_fork);
	sleep_aware(p->prog->t_eat * 1000, &p->prog->sim_stop);
	pthread_mutex_unlock(p->l_fork);
	return (NULL);
}
