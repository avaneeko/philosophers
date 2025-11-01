/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:35:19 by losypenk          #+#    #+#             */
/*   Updated: 2025/11/01 13:35:43 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//$ This file implements the philosopher simulation.

void	check_all_eaten(t_prog *p)
{
	unsigned int	i;

	i = 0;
	while (i < p->n_philo)
	{
		if (p->philos[i].n_eaten < p->n_to_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&p->print_acq);
	p->sim_stop = 1;
	pthread_mutex_unlock(&p->print_acq);
}

void	monitor(t_prog *p)
{
	unsigned long	now;
	unsigned int	i;

	while (p->sim_stop == 0)
	{
		now = now_ms(p->start_time);
		i = 0;
		while (i < p->n_philo)
		{
			if (now - p->philos[i].last_meal >= p->t_die)
			{
				pthread_mutex_lock(&p->print_acq);
				log_state_no_critical(&p->philos[i], MSG_DIED);
				p->sim_stop = 1;
				pthread_mutex_unlock(&p->print_acq);
				break ;
			}
			if (p->n_to_eat != ~0u && p->philos[i].n_eaten < p->n_to_eat)
				break ;
			i++;
		}
		check_all_eaten(p);
		usleep(100);
	}
}

void	start_simulation(t_prog *p)
{
	unsigned int	i;

	p->s_barrier = 1;
	monitor(p);
	i = 0;
	while (i < p->n_philo)
	{
		pthread_join(p->th[i], NULL);
		i++;
	}
}
